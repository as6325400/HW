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
          <a-menu-item key="3">Tom</a-menu-item>
          <a-menu-item key="4">Bill</a-menu-item>
          <a-menu-item key="5">Alex</a-menu-item>
        </a-sub-menu>
      </a-menu>
    </a-layout-sider>
    <a-layout>
      <a-layout-header style="background: #fff; padding: 0">
        <div class="flex">
          <InfoHeader class="ml-auto" @update-click="update_click" :username="username" />
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
              <div><h3>1</h3></div>
              <div><h3>2</h3></div>
              <div><h3>3</h3></div>
              <div><h3>4</h3></div>
            </a-carousel>
          <div class="polls-container mt-4">
            <div class="poll" v-for="(poll, index) in polls" :key="index">
              <PollComponent/>
            </div>
          </div>
        </div>
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Design ©2024 Created by as6325400
      </a-layout-footer>
    </a-layout>
  </a-layout>
  <UpdateComponent v-model:open="isModalVisible" />
</template>
<script lang="ts" setup>
import {
  PieChartOutlined,
  DesktopOutlined,
  UserOutlined,
  TeamOutlined,
  FileOutlined
} from '@ant-design/icons-vue'
import InfoHeader from '@/components/main/HeaderComponent.vue'
import UpdateComponent from '@/components/main/UpdateComponent.vue'
import { onMounted, ref } from 'vue'
import { fetchUserDataWithToken } from '@/functions/user'
import PollComponent from '@/components/main/PollComponent.vue'

let username = ref('')

onMounted(async () => {
  // const data = await fetchUserDataWithToken()
  // username.value = data.username
  username.value = 'admin'
})

const collapsed = ref<boolean>(false)
const selectedKeys = ref<string[]>(['1'])
const isModalVisible = ref(false)
const update_click = () => {
  isModalVisible.value = true
  console.log('update_click')
}

const polls = ref([
  { 
    id: 1,
    title: "問題一",
    description: "描述一",
    options: [{ id: 101, text: "選項 A", votes: 10 }, { id: 102, text: "選項 B", votes: 5 }]
  },
  { 
    id: 2,
    title: "問題二",
    description: "描述二",
    options: [{ id: 201, text: "選項 C", votes: 3 }, { id: 202, text: "選項 D", votes: 7 }]
  },
  { 
    id: 3,
    title: "問題二",
    description: "描述二",
    options: [{ id: 201, text: "選項 C", votes: 3 }, { id: 202, text: "選項 D", votes: 7 }]
  }
  // 更多投票模塊...
])

const vote = (pollId, optionId) => {
  const poll = polls.value.find(p => p.id === pollId)
  const option = poll.options.find(o => o.id === optionId)
  option.votes++
}

const calculatePercentage = (votes, pollId) => {
  const poll = polls.value.find(p => p.id === pollId)
  const totalVotes = poll.options.reduce((total, option) => total + option.votes, 0)
  return totalVotes > 0 ? ((votes / totalVotes) * 100).toFixed(0) : 0
}

const isSelected = (pollId, optionId) => {
  const poll = polls.value.find(p => p.id === pollId)
  const option = poll.options.find(o => o.id === optionId)
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
  background: #d3d3d3 ;
  overflow: hidden;
}
:deep(.slick-slide h3) {
  color: #fff;
}

</style>
