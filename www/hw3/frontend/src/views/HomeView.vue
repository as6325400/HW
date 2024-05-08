<template>
  <a-layout style="min-height: 100vh">
    <a-layout-sider v-model:collapsed="collapsed" collapsible>
      <div class="logo" />
      <a-menu v-model:selectedKeys="selectedKeys" theme="dark" mode="inline">
        <a-sub-menu key="sub1">
          <template #title>
            <span>
              <user-outlined />
              <span>User</span>
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
          <InfoHeader class="ml-auto" @update-click="update_click" />
          <div class="w-10"></div>
        </div>
      </a-layout-header>
      <a-layout-content style="margin: 0 16px">
        <a-breadcrumb style="margin: 16px 0">
          <a-breadcrumb-item>User</a-breadcrumb-item>
          <a-breadcrumb-item>Bill</a-breadcrumb-item>
        </a-breadcrumb>
        <div :style="{ padding: '24px', background: '#fff', minHeight: '360px' }">
          Bill is a cat.
        </div>
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Ant Design ©2018 Created by Ant UED
      </a-layout-footer>
    </a-layout>
  </a-layout>
  <!-- <a-modal
    v-model:visible="isModalVisible"
    title="Users Profile"
    @ok="handleOk"
    @cancel="handleCancel"
  >
    <form class="space-y-4">
      <div>
        <label>Username:</label>
        <a-input v-model="profile.username" placeholder="Username" />
      </div>
      <div>
        <label>Password:</label>
        <a-input type="password" v-model="profile.password" placeholder="Password" />
      </div>
      <div>
        <label>Photo:</label>
        <a-input v-model="profile.photo" placeholder="Upload Photo" />
      </div>
      <div>
        <label>Current Password:</label>
        <a-input
          type="password"
          v-model="currentPassword"
          placeholder="Input current password to save changes"
        />
      </div>
    </form>
  </a-modal> -->
  <UpdateComponent :isModalVisible="isModalVisible" />
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
import { ref } from 'vue'
const collapsed = ref<boolean>(false)
const selectedKeys = ref<string[]>(['1'])
// const profile = ref({
//   username: 'admin',
//   password: '',
//   photo: ''
// })
// const currentPassword = ref('')
const isModalVisible = ref(true)
// function handleOk() {
//   console.log('Submitted:', profile.value)
//   isModalVisible.value = false
// }

// function handleCancel() {
//   isModalVisible.value = false
// }

const update_click = () => {
  isModalVisible.value = true
  console.log('update_click')
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
</style>
