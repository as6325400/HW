<template>
  <!-- 統一的卡片包含標題、內容和投票選項 -->
  <a-card class="p-4 shadow-lg">
    <!-- 標題和內容介紹 -->
    <div class="mb-4 flex">
      <div>
        <h1 class="text-lg font-bold">{{ props.title }}</h1>
        <p>{{ props.description }}</p>
      </div>
      <InfoHeader
        class="ml-auto"
        :clickable="false"
        :username="props.username"
        :imgpath="props.imgpath"
      />
    </div>
    <!-- 投票選項 -->
    <div v-for="(option, index) in options" :key="index" class="mt-2">
      <a-button
        block
        @click="vote(option.id)"
        :type="selected === option.id ? 'primary' : 'default'"
        class="w-full"
      >
        {{ option.text }} - 票數: {{ option.votes }} (投票率:
        {{ calculatePercentage(option.votes) }}%)
      </a-button>
    </div>
  </a-card>
</template>

<script setup>
import { onMounted, ref } from 'vue'
import InfoHeader from '@/components/main/HeaderComponent.vue'
import { getVote, deletegetvote } from '@/functions/vote'
import { number } from 'yup'

const props = defineProps({
  username: {
    type: String,
    value: 'default'
  },
  imgpath: {
    type: String,
    value: null
  },
  description: {
    type: String,
    value: 'default'
  },
  title: {
    type: String,
    value: 'default'
  },
  options: {
    type: Array,
    value: []
  },
  topic_id: {
    type: String,
    value: null
  },
  user_option: {
    type: Number,
    value: null
  }
})

const options = ref([])

onMounted(() => {
  for (let i = 0; i < props.options.length; i++) {
    options.value.push({
      id: props.options[i].id,
      text: props.options[i].text,
      votes: props.options[i].votes
    })
  }
  console.log(props.imgpath)
  console.log(props.user_option)
  if (props.user_option !== null && props.user_option !== undefined) {
    selected.value = props.user_option
  }
})

const selected = ref(null)

const vote = async (optionId) => {
  const option = options.value.find((o) => o.id === optionId)
  if (selected.value === optionId) {
    selected.value = null
    option.votes--
    const res = await deletegetvote(props.topic_id, optionId, props.username)
    console.log(res)
    return
  }
  if (selected.value !== null) {
    const selectedOption = options.value.find((o) => o.id === selected.value)
    selectedOption.votes--
  }
  option.votes++
  selected.value = optionId
  console.log(props.topic_id, optionId, props.username)
  const res = await getVote(props.topic_id, optionId, props.username)
  // console.log()
}

const calculatePercentage = (votes) => {
  const totalVotes = options.value.reduce((total, option) => total + option.votes, 0)
  return totalVotes > 0 ? ((votes / totalVotes) * 100).toFixed(0) : 0
}
</script>

<style scoped>
/* 使用 Tailwind CSS 進行樣式設計 */
</style>
