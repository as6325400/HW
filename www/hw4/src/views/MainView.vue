<template>
  <div id="app">
    <svg width="500" height="500" style="border:1px solid #00000060;">
      <g class="counties"></g>
      <path class="county-borders"></path>
    </svg>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import * as d3 from 'd3'
import * as topojson from 'topojson-client'
import taiwan_County  from '../assets/taiwan-county.json'

const taiwanCountry = ref([])

const fetchMapData = async () => {
  const response = taiwan_County;
  console.log(response)
  const result = response
  taiwanCountry.value = result
  draw(taiwanCountry.value)
}

const draw = (mapData) => {
  const projection = d3.geoMercator().center([123, 24]).scale(5500)
  const path = d3.geoPath(projection)

  d3.select('g.counties')
    .selectAll('path')
    .data(topojson.feature(mapData, mapData.objects['taiwan-county']).features)
    .enter()
    .append('path')
    .attr('d', path)

  d3.select('path.county-borders')
    .attr('d', path(topojson.mesh(mapData, mapData.objects['taiwan-county'], (a, b) => a !== b)))
}

onMounted(() => {
  fetchMapData()
})
</script>

<style scoped>
/* 你可以在這裡加入一些樣式 */
</style>
