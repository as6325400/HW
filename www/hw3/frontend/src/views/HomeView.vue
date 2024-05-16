<template>
  <a-layout style="min-height: 100vh">
    <a-layout-sider v-model:collapsed="collapsed" collapsible>
      <div class="logo" />
      <a-menu v-model:selectedKeys="selectedKeys" theme="dark" mode="inline">
        <a-sub-menu key="sub1">
          <template #title>
            <span>
              <user-outlined />
              <span>{{ username }}</span>
            </span>
          </template>
          <a-menu-item key="3">
            <router-link to="/home">Home</router-link>
          </a-menu-item>
          <a-menu-item key="4">
            <router-link to="/poll">Poll page</router-link>
          </a-menu-item>
        </a-sub-menu>
      </a-menu>
    </a-layout-sider>
    <a-layout>
      <a-layout-header style="background: #fff; padding: 0">
        <div class="flex">
          <InfoHeader
            class="ml-auto"
            @update-click="update_click"
            :username="username"
            :imgpath="imgpath"
          />
          <div class="w-10"></div>
        </div>
      </a-layout-header>
      <a-layout-content style="margin: 0 16px">
        <a-breadcrumb style="margin: 16px 0">
          <a-breadcrumb-item>User</a-breadcrumb-item>
          <a-breadcrumb-item>{{ username }}</a-breadcrumb-item>
        </a-breadcrumb>
        <div :style="{ padding: '24px', background: '#fff', minHeight: '360px' }">
          <a-carousel autoplay>
            <div>User Number: {{ usernumber }}</div>
            <div>Topic Number: {{ topicnumber }}</div>
          </a-carousel>
          <div class="polls-container mt-4">
            <div class="poll" v-for="(poll, index) in polls" :key="index">
              <PollComponent
                :username="poll.ownername"
                :imgpath="poll.ownerphoto"
                :title="poll.title"
                :description="poll.description"
                :options="poll.options"
                :topic_id="poll.id"
                :user_option="poll.user_option"
              />
            </div>
          </div>
        </div>
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Design ©2024 Created by as6325400
      </a-layout-footer>
    </a-layout>
  </a-layout>
  <UpdateComponent v-model:open="isModalVisible" :imgpath="imgpath" :username="username" />
</template>
<script lang="ts" setup>
import { UserOutlined } from '@ant-design/icons-vue'
import InfoHeader from '@/components/main/HeaderComponent.vue'
import UpdateComponent from '@/components/main/UpdateComponent.vue'
import { onMounted, ref } from 'vue'
import { fetchUserDataWithToken } from '@/functions/user'
import { getAllVotes } from '@/functions/vote'
import PollComponent from '@/components/main/PollComponent.vue'

let username = ref('')
let usernumber = ref('')
let topicnumber = ref('')
let imgpath = ref('')
let polls = ref([])

onMounted(async () => {
  const data = await fetchUserDataWithToken()
  console.log(data)
  if (data.status === 487 || data.statusText === 'Unauthorized') {
    console.log('Unauthorized')
    window.location.href = '/login'
    return
  }
  username.value = data.user.username
  usernumber.value = data.people_num
  topicnumber.value = data.topic_num
  imgpath.value = import.meta.env.VITE_BACKEND + data.user.photo
  console.log('imgpath', imgpath.value)
  const res: Array = await getAllVotes()
  const allVotes = res.data.topics
  console.log(allVotes)
  for (let i = 0; i < allVotes.length; i++) {
    let user_option = null
    let options = []
    for (let j = 0; j < allVotes[i].options.length; j++) {
      options.push({
        id: allVotes[i].options[j].id,
        text: allVotes[i].options[j].item_name,
        votes: allVotes[i].options[j].vote_count
      })
      console.log(allVotes[i].options[j].voter.username, username.value)
      for (let k = 0; k < allVotes[i].options[j].voter.length; k++) {
        if (allVotes[i].options[j].voter[k].username == username.value) {
          user_option = allVotes[i].options[j].id
        }
      }
    }
    polls.value.push({
      id: Number(allVotes[i].id),
      title: allVotes[i].topic_name,
      description: allVotes[i].title,
      options: options,
      ownername: allVotes[i].ownername,
      ownerphoto: import.meta.env.VITE_BACKEND + allVotes[i].ownerpath,
      user_option: user_option
    })
    // console.log(polls.value)
  }
  console.log(polls.value)
})

const collapsed = ref<boolean>(false)
const selectedKeys = ref<string[]>(['3'])
const isModalVisible = ref(false)
const update_click = () => {
  isModalVisible.value = true
  console.log('update_click')
}

const vote = (pollId, optionId) => {
  const poll = polls.value.find((p) => p.id === pollId)
  const option = poll.options.find((o) => o.id === optionId)
  option.votes++
}

const calculatePercentage = (votes, pollId) => {
  const poll = polls.value.find((p) => p.id === pollId)
  const totalVotes = poll.options.reduce((total, option) => total + option.votes, 0)
  return totalVotes > 0 ? ((votes / totalVotes) * 100).toFixed(0) : 0
}

const isSelected = (pollId, optionId) => {
  const poll = polls.value.find((p) => p.id === pollId)
  const option = poll.options.find((o) => o.id === optionId)
  return option.selected // 或者其他方式標記已選擇選項
}
</script>
<style scoped>
#components-layout-demo-side .logo {
  height: 32px;
  margin: 16px;
  background: rgba(255, 255, 255, 0.3);
}

.site-layout .site-layout-background {
  background: #fff;
}
[data-theme='dark'] .site-layout .site-layout-background {
  background: #141414;
}
.polls-container {
  display: flex;
  flex-wrap: wrap;
  gap: 16px; /* 每個卡片之間的間隙 */
}

.poll {
  flex: 1 1 48%; /* 每個投票卡片佔一行的 48%，兩個加起來接近 100%，考慮到間隙 */
}

:deep(.slick-slide) {
  text-align: center;
  height: 160px;
  line-height: 160px;
  background: #d3d3d3;
  overflow: hidden;
}
:deep(.slick-slide h3) {
  color: #fff;
}
</style>
