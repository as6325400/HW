<template>
  <svg class="w-full h-full border border-gray-300" ref = "svgElement">
    <g class="counties mx-auto"></g>
    <path class="county-borders"></path>
    <text id="county-name" x="10" y="30" font-size="20" fill="black"></text>
    <foreignObject id="chart-container" x="10" y="50" width="300" height="200" class="hidden">
      <div xmlns="http://www.w3.org/1999/xhtml">
        <canvas id="election-chart"></canvas>
      </div>
    </foreignObject>
    <foreignObject x="10" y="10" width="300" height="30" ref="yearSelect" class="hidden">
      <div xmlns="http://www.w3.org/1999/xhtml">
        <select id="county-select" v-model="search_year">
          <option value="2024" selected>2024</option>
          <option value="2020">2020</option>
          <option value="2016">2016</option>
        </select>
      </div>
    </foreignObject>
  </svg>
</template>

<script setup>
import { ref, onMounted, watch } from 'vue'
import { useRouter } from 'vue-router'
import * as d3 from 'd3'
import * as topojson from 'topojson-client'
import Chart from 'chart.js/auto'
import taiwan_County  from '@/assets/taiwan-county.json'
import taiwan_Town from '@/assets/taiwan-town.json'
import {getdata} from '@/functions/data'


const taiwanCountry = ref([])
const router = useRouter()
let electionChart = null;
const yearSelect = ref(null)
const svgElement = ref(null)
const search_year = ref(2024)

watch(() => search_year.value, async(value) => {
  d3.select('g.counties').selectAll('path').remove();
  d3.select('path.county-borders').selectAll('path').remove();
  const electionData = await getdata('臺灣', value)
  console.log(value)
  draw(taiwanCountry.value, electionData)
})


const draw = (mapData, electionData) => {
  const svg = d3.select('svg')
  const width = svg.node().clientWidth
  const height = svg.node().clientHeight
  const projection = d3.geoMercator().center([120.75, 23.8]).scale(8000).translate([width / 2, height / 2])
  const path = d3.geoPath(projection)

  const colorScale = d3.scaleOrdinal()
    .domain(['party1', 'party2', 'party3'])
    .range([electionData[0].candidate1_color, electionData[0].candidate2_color, electionData[0].candidate3_color])
  
  const intensityScale = d3.scaleLinear()
    .domain([20, 25, 30, 35, 40, 45, 50])
    .range([0.1, 0.2, 0.4, 0.5, 0.6, 0.8, 1])


  d3.select('g.counties')
    .selectAll('path')
    .data(topojson.feature(mapData, mapData.objects['COUNTY_MOI_1080617']).features)
    .enter()
    .append('path')
    .attr('d', path)
    .attr('fill', d => {
      const countyName = d.properties.COUNTYNAME
      const countyData = electionData.find(e => e.county_name === countyName)
      const { candidate1_vote_rate, candidate2_vote_rate, candidate3_vote_rate } = countyData;
      const voteRates = [
          { party: 'party1', rate: candidate1_vote_rate },
          { party: 'party2', rate: candidate2_vote_rate },
          { party: 'party3', rate: candidate3_vote_rate }
        ];
      console.log(countyName)
      const leadingPartyData = voteRates.find(data => data.rate === d3.max(voteRates, d => d.rate));
      console.log(leadingPartyData)
      const leadingParty = leadingPartyData.party;
      const color = d3.color(colorScale(leadingParty));
      if (color) {
        color.opacity = intensityScale(Number(d3.max(voteRates, d => d.rate)) * 100);
        return color.toString();
      }
      return 'gray'
    })
    .on('click', (event, d) => {
      const countyName = d.properties.COUNTYNAME;
      console.log(countyName)
      let year = search_year.value.toString()
      router.push({ name: 'town', params: { countyName, year} });
    })
    .on('mouseover', (event, d) => {
      const countyName = d.properties.COUNTYNAME;
      d3.select('#county-name').text(countyName);

      const countyData = electionData.find(e => e.county_name === countyName);
      if (countyData) {
        showChart(countyData);
      }
      console.log('mouseover')
      d3.select('#chart-container').style('display', 'block');
    })
    .on('mouseout', () => {
      d3.select('#county-name').text('');
      d3.select('#chart-container').style('display', 'none');
    });

  d3.select('path.county-borders')
    .attr('d', path(topojson.mesh(mapData, mapData.objects['COUNTY_MOI_1080617'])))
}

const showChart = (countyData) => {
  const chartElement = document.getElementById('election-chart');
  const ctx = chartElement.getContext('2d');

  // 確認圖表元素的尺寸是固定的
  if (electionChart) {
    electionChart.destroy();
  }
  electionChart = new Chart(ctx, {
    type: 'bar',
    data: {
      labels: ['', '', ''],
      datasets: [{
        label: '',
        data: [countyData.candidate1_vote_rate, countyData.candidate2_vote_rate, countyData.candidate3_vote_rate],
        backgroundColor: [countyData.candidate1_color, countyData.candidate2_color, countyData.candidate3_color]
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      scales: {
        x: {
          grid: {
            display: false
          },
          ticks: {
            display: false // 移除底部的 x 軸標籤
          }
        },
        y: {
          beginAtZero: true,
          grid: {
            display: false
          },
          ticks: {
            display: false // 移除左側標籤
          }
        }
      },
      plugins: {
        legend: {
          display: false // 移除圖例
        }
      },
      animation: {
        duration: 0 // 禁用動畫
      }
    }
  });
}



onMounted(async() => {
  taiwanCountry.value = taiwan_County;
  const electionData = await getdata('臺灣', search_year.value)
  draw(taiwanCountry.value, electionData)

  const svg = svgElement.value;
  const svgWidth = svg.clientWidth;
  const svgHeight = svg.clientHeight;
  const select_year = yearSelect.value;
  select_year.classList.remove('hidden');
  select_year.setAttribute('x', svgWidth - 150); // 調整 x 坐標，使按鈕至右
  select_year.setAttribute('y', 20); // 調整 y 坐標，使按鈕至下
  console.log(select_year)
})
</script>
