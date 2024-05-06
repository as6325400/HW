<template>
  <Title></Title>
  <DynamicForm :fields="fields" buttonText="Login" @button-click="handler" />
</template>

<script setup>
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
const fields = [
  {
    id: 'username',
    name: 'username',
    type: 'text',
    placeholder: 'Username'
  },
  {
    id: 'password',
    name: 'password',
    type: 'password',
    placeholder: 'Password'
  }
]

const handler = () => {
  console.log('Login button clicked')
}
</script>
