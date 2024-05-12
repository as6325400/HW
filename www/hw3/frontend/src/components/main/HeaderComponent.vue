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
import { ref, watch } from 'vue'
import { UserOutlined } from '@ant-design/icons-vue'
import { Avatar, Button, Popover, Space } from 'ant-design-vue'
import { defineEmits, defineProps } from 'vue'
import { Logout } from '@/functions/user'

const isOpen = ref(false)

watch(isOpen, (val) => {
  if (!props.clickable) {
    isOpen.value = false
  }
})

const props = defineProps({
  username: {
    type: String,
    default: 'Username'
  },
  imgpath: {
    type: String,
    default: null
  },
  clickable: {
    type: Boolean,
    default: true
  }
})

function togglePopover() {
  console.log(props.clickable, isOpen.value)
  if (props.clickable) {
    console.log('Toggling popover...')
    isOpen.value = !isOpen.value
  }
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
