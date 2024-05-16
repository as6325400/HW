<template>
  <a-table :columns="columns" :data-source="dataSource" :pagination="pagination" bordered>
    <template #bodyCell="{ column, text, record }">
      <div v-if="column.dataIndex === 'Create_Time'">
        {{ text }}
      </div>
      <div v-if="['Topics', 'title', 'option'].includes(column.dataIndex)">
        <div>
          <a-input
            v-if="editableData[record.key]"
            v-model:value="editableData[record.key][column.dataIndex]"
            style="margin: -5px 0"
          />
          <template v-else>
            {{ text }}
          </template>
        </div>
      </div>
      <div v-else-if="column.dataIndex === 'operation'">
        <div class="editable-row-operations">
          <span v-if="editableData[record.key]">
            <a-typography-link @click="save(record.key)">Save</a-typography-link>
            <a-typography-text
              @click="delete_item(record.key)"
              class="text-red-600 mr-2 hover:text-red-800"
              >Delete</a-typography-text
            >
            <a-popconfirm title="Sure to cancel?" @confirm="cancel(record.key)">
              <a>Cancel</a>
            </a-popconfirm>
          </span>
          <span v-else>
            <a @click="edit(record.key)">Edit</a>
          </span>
        </div>
      </div>
    </template>
  </a-table>
</template>

<script lang="ts" setup>
import { cloneDeep } from 'lodash-es'
import { defineProps, reactive, toRefs, defineExpose } from 'vue'
import { CreateVote, DeleteVote, gettime, EditVote } from '@/functions/vote'

const pagination = reactive({
  pageSizeOptions: ['10', '20', '30', '50'],
  showSizeChanger: true,
  defaultPageSize: 10
})

const props = defineProps({
  initialData: Array
})

const columns = [
  {
    title: 'Topics',
    dataIndex: 'Topics',
    width: '10%'
  },
  {
    title: 'Title',
    dataIndex: 'title',
    width: '15%'
  },
  {
    title: 'Create Time',
    dataIndex: 'Create_Time',
    width: '15%'
  },
  {
    title: 'option',
    dataIndex: 'option',
    width: '40%'
  },
  {
    title: 'operation',
    dataIndex: 'operation'
  }
]

const dataSource = reactive(props.initialData)
const editableData: UnwrapRef<Record<string, DataItem>> = reactive({})

const edit = (key: string) => {
  console.log(key)
  editableData[key] = cloneDeep(dataSource.find((item) => item.key === key))
}

function splitString(input: string): string[] {
  return input
    .split(/(?<!\\),/)
    .map((part) => part.replace(/\\,/g, ','))
    .map((part) => part.trim())
}

const save = async (key: string) => {
  Object.assign(
    dataSource.find((item) => item.key === key),
    editableData[key]
  )
  const item = dataSource.find((item) => item.key === key)
  if (item.Topics.trim() === '' || item.title.trim() === '' || item.option.trim() === '') {
    alert('Please fill in all the fields')
    return
  }
  let response = null;
  if(item.type == 'new') response = await CreateVote(item.Topics, item.title, splitString(item.option))
  else if(item.type == 'old') response = await EditVote(item.Topics, item.title, splitString(item.option))
  if (response.status === 487) {
    alert('Please login')
    window.location.href = '/login'
    return
  }
  if (response.status === 488) {
    alert('The vote has already existed')
    return
  }
  console.log(response)
  const time = await gettime(item.Topics, item.title)
  dataSource.find((item) => item.key === key).Create_Time = time.data.time
  delete editableData[key]
}

const delete_item = async (key: string) => {
  const item = dataSource.find((item) => item.key === key)
  const response = await DeleteVote(item.Topics, item.title)
  console.log(response)
  if (response.status === 487) {
    alert('Please login')
    window.location.href = '/login'
    return
  }
  dataSource.splice(dataSource.indexOf(item), 1)
}

const cancel = (key: string) => {
  delete editableData[key]
}
defineExpose({
  edit
})
</script>

<style scoped>
.editable-row-operations a {
  margin-right: 8px;
}
</style>
