<template>
  <!-- 統一的卡片包含標題、內容和投票選項 -->
  <a-card class="p-4 shadow-lg">
    <!-- 標題和內容介紹 -->
    <div class="mb-4 flex">
      <div>
        <h1 class="text-lg font-bold">問題投票</h1>
        <p>請選擇下列選項進行投票，您的選擇對我們非常重要。</p>
      </div>
      <InfoHeader class="ml-auto" :clickable="false" :username="props.username" />
    </div>
    <!-- 投票選項 -->
    <div v-for="(option, index) in options" :key="index" class="mt-2">
      <a-button block @click="vote(option.id)" :type="selected === option.id ? 'primary' : 'default'" class="w-full">
        {{ option.text }} - 票數: {{ option.votes }} (投票率: {{ calculatePercentage(option.votes) }}%)
      </a-button>
    </div>
  </a-card>
</template>

<script setup>
import { ref } from 'vue'
import InfoHeader from '@/components/main/HeaderComponent.vue'

const props = defineProps({
  username:{
    type: String,
    value: 'default'
  },
  photo:{
    type: String,
    value: 'default'
  },
  description:{
    type: String,
    value: 'default'
  },
  title:{
    type: String,
    value: 'default'
  },
  options:{
    type: Array,
    value: []
  }
})

const options = ref([
  { id: 1, text: "你喜歡的不是綠茶婊", votes: 3 },
  { id: 2, text: "增知識面的論壇", votes: 1 },
  { id: 3, text: "車人戶、日曜、講、陳天橋", votes: 0 }
])
const selected = ref(null)

const vote = (optionId) => {
  const option = options.value.find(o => o.id === optionId)
  option.votes++
  selected.value = optionId
}

const calculatePercentage = (votes) => {
  const totalVotes = options.value.reduce((total, option) => total + option.votes, 0)
  return totalVotes > 0 ? ((votes / totalVotes) * 100).toFixed(0) : 0
}
</script>

<style scoped>
/* 使用 Tailwind CSS 進行樣式設計 */
</style>
