<template>
  <div class="whitespace-pre-wrap">
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
  errorMsg.value = ''
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
  const str = data.password;
  const hasUpperCase = /[A-Z]/.test(str);
  const hasLowerCase = /[a-z]/.test(str);
  const hasNumber = /\d/.test(str);
  const isLongEnough = str.length >= 6;

  let arr = [0, 0, 0, 0]
  let errorMsg_arr = [
    'Password must include an uppercase letter.',
    'Password must include a lowercase letter.',
    'Password must include a number.',
    'Password must be at least 6 characters long.'
  ];
  if (!hasUpperCase) {
    arr[0] = 1
  }
  if (!hasLowerCase) {
    arr[1] = 1
  }
  if (!hasNumber) {
    arr[2] = 1
  }
  if (!isLongEnough) {
    arr[3] = 1
  }
  for(let i = 0; i < 4; i++) {
    if (arr[i] === 1) {
      errorMsg.value += errorMsg_arr[i] + '\n'
    }
  }

  if (errorMsg.value !== '') {
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
      window.location.href = '/login'
    } else {
      errorMsg.value = 'Register failed'
      console.log(res)
    }
  })

}
</script>
