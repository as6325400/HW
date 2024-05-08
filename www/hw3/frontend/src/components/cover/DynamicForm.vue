<template>
  <form class="bg-white p-8 rounded-lg shadow-md w-full max-w-sm mx-auto mt-10">
    <header class="text-center my-2 text-slate-300">
      <slot name="header"></slot>
    </header>
    <div v-for="field in fields" :key="field.id" class="mb-6">
      <input
        :placeholder="field.placeholder"
        :type="field.type"
        :id="field.id"
        :name="field.name"
        v-model="field.value"
        autocomplete="new-password"
        class="mt-1 block w-full px-3 py-2 border border-gray-300 rounded-md shadow-sm focus:outline-none focus:ring-indigo-500 focus:border-indigo-50"
      />
    </div>
    <button :class="buttonClass" type="submit" @click="onClick">
      {{ buttonText }}
    </button>
    <div>
      <router-link :to="linkTo" class="text-blue-500 hover:text-blue-700">
        {{ linkText }}
      </router-link>
    </div>
    <div class="text-center mt-2" :class="linkClass">
      <slot name="link"></slot>
    </div>
  </form>
</template>

<script setup>
const props = defineProps({
  fields: Array,
  buttonText: {
    type: String,
    default: 'Submit'
  },
  buttonClass: {
    type: String,
    default:
      'w-full bg-blue-600 text-white font-bold py-2 rounded hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-500 focus:ring-opacity-50'
  },
  linkText: {
    type: String,
    default: ''
  },
  linkTo: {
    type: String,
    default: ''
  },
  linkClass: {
    type: String,
    default: ''
  }
})

const emit = defineEmits(['button-click'])

function onClick(event) {
  event.preventDefault()
  emit('button-click')
}
</script>
