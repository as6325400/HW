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
  // 使用正則表達式匹配未被反斜杠轉義的逗號，然後分割字符串
  // 正則表達式解釋：匹配一個非反斜杠的或字符串開頭的位置後跟一個逗號
  return input
    .split(/(?<!\\),/)
    .map((part) => part.replace(/\\,/g, ',')) // 將轉義的逗號換成普通逗號
    .map((part) => part.trim()) // 去除每個元素前後的空白
}

const save = (key: string) => {
  Object.assign(
    dataSource.find((item) => item.key === key),
    editableData[key]
  )
  const item = dataSource.find((item) => item.key === key)
  console.log(item)
  console.log(item.Topics)
  console.log(splitString(item.option))
  if (item.Topics.trim() === '' || item.title.trim() === '' || item.option.trim() === '') {
    alert('Please fill in all the fields')
    return
  }
  delete editableData[key]
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
