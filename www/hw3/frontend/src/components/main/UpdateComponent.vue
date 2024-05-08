<template>
  <a-modal :v-model:visible="isModalVisible" :title="title" @ok="handleOk" @cancel="handleCancel">
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
  </a-modal>
</template>

<script setup>
import { ref } from 'vue'
import { defineProps } from 'vue'
const props = defineProps({
  isModalVisible: {
    type: Boolean,
    default: true
  },
  title: {
    type: String,
    default: 'Users Profile'
  }
})

const profile = ref({
  username: 'admin',
  password: '',
  photo: ''
})
const currentPassword = ref('')
function handleOk() {
  console.log('Submitted:', profile.value)
  isModalVisible.value = false
}

function handleCancel() {
  isModalVisible.value = false
}
</script>
