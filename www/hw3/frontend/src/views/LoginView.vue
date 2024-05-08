<template>
  <div>
    <Title></Title>
    <DynamicForm
      :fields="fields"
      buttonText="Login"
      linkText="還未註冊?點此建立"
      linkTo="/"
      :linkClass="errorMsgClass"
      @button-click="loginHandler"
    >
      <template #header> Sign in to start your session </template>
      <template #link>
        {{ errorMsg }}
      </template>
    </DynamicForm>
  </div>
</template>

<script setup>
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import { ref } from 'vue'
import { Login } from '@/functions/user'

let errorMsgClass = ref('text-red-500')
let errorMsg = ref('')

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
  Login({ email: data.email, password: data.password }).then((res) => {
    console.log(res.status)
    if (res.status === 200) {
      errorMsgClass.value = 'text-green-500'
      errorMsg.value = 'Login success'
      localStorage.setItem('token', res.data.token)
      setTimeout(() => {
        window.location.href = '/home'
      }, 1000)
    } else {
      errorMsg.value = 'Login failed'
    }
  })
}
</script>
