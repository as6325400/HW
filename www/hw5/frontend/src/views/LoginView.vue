<template>
  <div>
    <Title></Title>
    <DynamicForm
      :fields="fields"
      buttonText="Login"
      linkText="還未註冊?點此建立"
      linkTo="/register"
      :linkClass="errorMsgClass"
      @button-click="loginHandler"
    >
      <template #header> Sign in to start your session </template>
      <template #link>
        {{ errorMsg }}
      </template>
    </DynamicForm>
    <GoogleSignInButton></GoogleSignInButton>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import GoogleSignInButton from '@/components/cover/GoogleSignInButton.vue';

const fields = ref([
  {
    id: 'email',
    name: 'email',
    type: 'text',
    placeholder: 'email',
    value: ''
  },
  {
    id: 'password',
    name: 'password',
    type: 'password',
    placeholder: 'Password',
    value: ''
  }
])

const loginHandler = () => {
  errorMsgClass.value = 'text-red-500'
  const data = fields.value.reduce((result, field) => {
    result[field.id] = field.value
    return result
  }, {})
  if (!data.email || !data.password) {
    errorMsg.value = 'All fields are required'
    return
  }
}

</script>