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
    <foreignObject id="back-button" width="100" height="50" ref="backButton" class="hidden">
      <div xmlns="http://www.w3.org/1999/xhtml">
        <button @click="goBack" style="background-color: gray; padding: 5px; border-radius: 5px;">返回上一頁</button>
      </div>
    </foreignObject>
  </svg>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import * as d3 from 'd3'
import * as topojson from 'topojson-client'
import Chart from 'chart.js/auto'
import { useRoute } from 'vue-router'
import taiwan_Town from '@/assets/taiwan-town.json'
import {getdata} from '@/functions/data'

const taiwanCountry = ref([])
let electionChart = null;
const route = useRoute()
let countyName = ""
const svgElement = ref(null)
const backButton = ref(null)

const goBack = () => {
  window.location.href = '/'
}

var centers = {
  "基隆市": { center: [121.69, 25.11] },
  "臺北市": { center: [121.56, 25.08] },
  "新北市": { center: [121.64, 24.99] },
  "桃園市": { center: [121.23, 24.86] },
  "新竹市": { center: [120.95, 24.78] },
  "新竹縣": { center: [121.17, 24.69] },
  "苗栗縣": { center: [120.94, 24.51] },
  "臺中市": { center: [120.95, 24.22] },
  "彰化縣": { center: [120.45, 24.00] },
  "南投縣": { center: [120.98, 23.84] },
  "雲林縣": { center: [120.37, 23.66] },
  "嘉義縣": { center: [120.54, 23.43] },
  "嘉義市": { center: [120.45, 23.48] },
  "臺南市": { center: [120.34, 23.15] },
  "高雄市": { center: [120.58, 22.98] },
  "屏東縣": { center: [120.63, 22.39] },
  "臺東縣": { center: [121.18, 22.70] },
  "花蓮縣": { center: [121.38, 23.74] },
  "宜蘭縣": { center: [121.60, 24.55] },
  "澎湖縣": { center: [119.50, 23.47] },
  "金門縣": { center: [118.32, 24.45] },
  "連江縣": { center: [120.21, 26.17] },
};


const draw = (mapData, electionData) => {
  const svg = d3.select('svg')
  const width = svg.node().clientWidth
  const height = svg.node().clientHeight
  const projection = d3.geoMercator().center(centers[countyName].center).scale(17000).translate([width / 2, height / 2])
  const path = d3.geoPath(projection)

  const colorScale = d3.scaleOrdinal()
    .domain(['party1', 'party2', 'party3'])
    .range([electionData[0].candidate1_color, electionData[0].candidate2_color, electionData[0].candidate3_color])
  
  const intensityScale = d3.scaleLinear()
    .domain([20, 25, 30, 35, 40, 45, 50])
    .range([0.3, 0.5, 0.7, 0.8, 0.9, 1.0, 1.2])

  // console.log(topojson.feature(mapData, mapData.objects['TOWN_MOI_1080617']).features.filter(d => d.properties.COUNTYNAME === countyName))
  d3.select('g.counties')
    .selectAll('path')
    .data(topojson.feature(mapData, mapData.objects['TOWN_MOI_1080617']).features.filter(d => d.properties.COUNTYNAME === countyName))
    .enter()
    .append('path')
    .attr('d', path)
    .attr('fill', d => {
      console.log(d.properties)
      const countyName = d.properties.TOWNNAME
      console.log(electionData)
      const countyData = electionData.find(e => e.township_name === countyName)
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
    .on('mouseover', (event, d) => {
      console.log(d)
      const countyName = d.properties.TOWNNAME;
      d3.select('#county-name').text(countyName);
      console.log(electionData)
      const countyData = electionData.find(e => e.township_name === countyName);
      if (countyData) {
        showChart(countyData);
      }

      d3.select('#chart-container').style('display', 'block');
    })
    .on('mouseout', () => {
      d3.select('#county-name').text('');
      d3.select('#chart-container').style('display', 'none');
    });

  d3.select('path.county-borders')
    .attr('d', path(topojson.mesh(mapData, mapData.objects['TOWN_MOI_1080617'], (a, b) => a.properties.COUNTYNAME === countyName && b.properties.COUNTYNAME === countyName)))
}

const showChart = (countyData) => {
  const ctx = document.getElementById('election-chart').getContext('2d');
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
  countyName = route.params.countyName
  let year = route.params.year
  taiwanCountry.value = taiwan_Town;
  const electionData = await getdata(countyName, year)
  draw(taiwanCountry.value, electionData)

  const svg = svgElement.value;
  const backButtonElement = backButton.value;
  const svgWidth = svg.clientWidth;
  const svgHeight = svg.clientHeight;
  backButtonElement.classList.remove('hidden');
  backButtonElement.setAttribute('x', svgWidth / 2 - 50); // 調整 x 坐標，使按鈕居中
  backButtonElement.setAttribute('y', svgHeight - 60); // 調整 y 坐標，使按鈕位於底部
})
</script>
