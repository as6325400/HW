<template>
  <a-layout style="min-height: 100vh">
    <a-layout-sider v-model:collapsed="collapsed" collapsible>
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
          <a-breadcrumb-item>用戶</a-breadcrumb-item>
          <a-breadcrumb-item>{{ username }}</a-breadcrumb-item>
        </a-breadcrumb>
        <div class="flex">
          <a-button type="primary" class="mx-4" @click="addEmptyRow">Primary Button</a-button>
          <a-input-search
            placeholder="Search"
            v-model:value="searchQuery"
            style="margin-bottom: 16px"
          />
        </div>
        <!-- <a-table :columns="columns" :dataSource="filteredData" rowKey="id"></a-table> -->
        <PollTable ref="table" :initialData="ownpolldata" />
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Design ©2024 Created by as6325400
      </a-layout-footer>
    </a-layout>
  </a-layout>
  <UpdateComponent v-model:open="isModalVisible" :imgpath="imgpath" :username="username" />
</template>

<script setup>
import { ref, computed, onMounted, watch } from 'vue'
import PollTable from '@/components/main/PollTable.vue'
import InfoHeader from '@/components/main/HeaderComponent.vue'
import UpdateComponent from '@/components/main/UpdateComponent.vue'
import { fetchUserDataWithToken } from '@/functions/user'
import { UserOutlined } from '@ant-design/icons-vue'
import { getowntopics } from '@/functions/user'
import { cloneDeep } from 'lodash-es';
const pollTableRef = ref(null)
const selectedKeys = ref(['4'])
const searchQuery = ref('dawdwad')
const username = ref('Username')
const collapsed = ref(false)
const table = ref(null)
const imgpath = ref(null)
const isModalVisible = ref(false)
let ownpolldata = ref([])
let originpolldata = ref([])

watch(searchQuery, (val) => {
  if(val === '') {
    ownpolldata.value = originpolldata.value
    return
  }
  else{
    ownpolldata.value = originpolldata.value.filter((item) => {
      return item.title.includes(val) || item.Topics.includes(val)
    })
  }
})

onMounted(async () => {
  const data = await fetchUserDataWithToken()
  console.log(data)
  if (data.status === 487) {
    console.log('Unauthorized')
    window.location.href = '/login'
    return
  }
  username.value = data.user.username
  imgpath.value = import.meta.env.VITE_BACKEND + data.user.photo

  let poll_data = await getowntopics()
  console.log(poll_data.topics)
  for (let i = 0; i < poll_data.topics.length; i++) {
    const newkey = `new-${ownpolldata.value.length + 1}`
    ownpolldata.value.push({
      key: newkey,
      Topics: poll_data.topics[i].topic_name,
      title: poll_data.topics[i].title,
      Create_Time: poll_data.topics[i].time,
      option: poll_data.topics[i].options.join(', '),
      type: 'old'
    })
  }
  originpolldata = ref(cloneDeep(ownpolldata.value))
})

const update_click = () => {
  isModalVisible.value = true
  console.log('update_click')
}

const addEmptyRow = () => {
  const newkey = `new-${ownpolldata.value.length + 1}`
  ownpolldata.value.unshift({
    key: newkey,
    Topics: '',
    title: '',
    Create_Time: '',
    option: '',
    type: 'new'
  })
  table.value.edit(newkey)
}
</script>
