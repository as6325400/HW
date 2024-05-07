<template>
  <div>
    <Title></Title>
    <DynamicForm :fields="fields" buttonText="Login" linkText = "還未註冊?點此建立" 
    linkTo = "/" @button-click="loginHandler">
      <template #header>
        Sign in to start your session
      </template>
      <template #link>
        {{errorMsg}}
      </template>
    </DynamicForm>
  </div>
</template>

<script setup>
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import { ref, toValue } from 'vue'

let errorMsg = ref('')

const fields = ref([
  {
    id: 'username',
    name: 'username',
    type: 'text',
    placeholder: 'Username',
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
  const data = fields.value.reduce((result, field) => {
    result[field.id] = field.value;
    return result;
  }, {});
  if(!data.username || !data.password){
    errorMsg.value = 'All fields are required';
    return;
  }
}
</script>
