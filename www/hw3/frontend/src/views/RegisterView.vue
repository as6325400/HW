<template>
  <Title></Title>
  <DynamicForm :fields="fields" buttonText="Register" @button-click="RegisterHandler" >
    {{errorMsg}}
  </DynamicForm>
</template>

<script setup>
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import {ref} from 'vue'
import * as yup from 'yup';

const mailSchema = yup.string().email().required();
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
    result[field.id] = field.value;
    return result;
  }, {});
  if(!data.username || !data.email || !data.password || !data.confirmPassword){
    errorMsg.value = 'All fields are required';
    return;
  }
  if(!mailSchema.isValidSync(data.email)){
    errorMsg.value = 'Invalid email';
    return;
  }
  if(data.password !== data.confirmPassword){
    errorMsg.value = 'Passwords do not match';
    return;
  }
}
</script>
  