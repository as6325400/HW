<template>
  <Title></Title>
  <DynamicForm :fields="fields" buttonText="Register" @button-click="RegisterHandler" />
</template>

<script setup>
import Title from '@/components/cover/CoverTitle.vue'
import DynamicForm from '@/components/cover/DynamicForm.vue'
import {ref} from 'vue'

const fields = ref([
  {
    id: 'username',
    name: 'username',
    type: 'text',
    placeholder: 'Username'
  },
  {
    id: 'email',
    name: 'email',
    type: 'text',
    placeholder: 'email'
  },
  {
    id: 'password',
    name: 'password',
    type: 'password',
    placeholder: 'Password'
  },
  {
    id: 'confirmPassword',
    name: 'confirmPassword',
    type: 'password',
    placeholder: 'Confirm Password'
  }
])

const RegisterHandler = () => {
  const data = fields.value.reduce((result, field) => {
    result[field.id] = field.value;
    return result;
  }, {});
  console.log(data);
}
</script>
  