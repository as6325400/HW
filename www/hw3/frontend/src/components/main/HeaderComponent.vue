<template>
  <a-popover v-model:open="isOpen" placement="bottom" trigger="click">
    <template #content>
      <a-button block style="margin-bottom: 8px" @click="updateProfile">Update</a-button>
      <a-button block type="primary" @click="signOut">Sign out</a-button>
    </template>

    <a-space style="cursor: pointer" @click="togglePopover">
      <a-avatar :src="imgpath">
        <template #icon><UserOutlined /></template>
      </a-avatar>
      <span>{{ username }}</span>
    </a-space>
  </a-popover>
</template>

<script setup>
import { ref } from 'vue'
import { UserOutlined } from '@ant-design/icons-vue'
import { Avatar, Button, Popover, Space } from 'ant-design-vue'
import imageSrc from './images.jpeg' // 确保这里的文件名与你的图片文件名相匹配
import { defineEmits, defineProps } from 'vue'
import { Logout } from '@/functions/user'

const isOpen = ref(false)

const props = defineProps({
  username: {
    type: String,
    default: 'Username'
  },
  imgpath: {
    type: String,
    default: imageSrc
  }
})

function togglePopover() {
  isOpen.value = !isOpen.value
}

const emit = defineEmits(['update-click'])
function updateProfile() {
  console.log('Updating profile...')
  isOpen.value = false
  emit('update-click')
}

function signOut() {
  Logout()
  setTimeout(() => {
    window.location.href = '/login'
  }, 1000)
}
</script>

<style scoped>
/* Add any specific styles you need here */
</style>
