<template>
  <div>
    <Title></Title>
    <DynamicForm
      :fields="fields"
      buttonText="Register"
      linkText="已經註冊?點此登入"
      linkTo="/login"
      :linkClass="errorMsgClass"
      @button-click="RegisterHandler"
    >
      <template #header> Register to start your session </template>
      <template #link>
        {{ errorMsg }}
      </template>
    </DynamicForm>
  </div>
</template>

<script setup lang="ts">
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import { ref } from 'vue'
import * as yup from 'yup'
import { Register } from '@/functions/user'

const mailSchema = yup.string().email().required()
let errorMsg = ref('')
let errorMsgClass = ref('text-red-500')

const fields = ref([
  {
    id: 'username',
    name: 'username',
    type: 'text',
    placeholder: 'Username',
    value: ''
  },
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
  },
  {
    id: 'confirmPassword',
    name: 'confirmPassword',
    type: 'password',
    placeholder: 'Confirm Password',
    value: ''
  }
])

const RegisterHandler = () => {
  const data = fields.value.reduce((result, field) => {
    result[field.id] = field.value
    return result
  }, {})
  errorMsgClass.value = 'text-red-500'
  if (!data.username || !data.email || !data.password || !data.confirmPassword) {
    errorMsg.value = 'All fields are required'
    return
  }
  if (!mailSchema.isValidSync(data.email)) {
    errorMsg.value = 'Invalid email'
    return
  }
  if (data.password !== data.confirmPassword) {
    errorMsg.value = 'Passwords do not match'
    return
  }

  Register({
    username: data.username,
    email: data.email,
    password: data.password,
    password_confirmation: data.confirmPassword
  }).then((res) => {
    if (res.status === 201) {
      errorMsgClass.value = 'text-green-500'
      errorMsg.value = 'Register success'
    } else {
      errorMsg.value = 'Register failed'
    }
  })
}
</script>
