<template>
  <a-table :columns="columns" :data-source="dataSource" :pagination="pagination" bordered>
    <template #bodyCell="{ column, text, record }">
      <div v-if="['name', 'title', 'option'].includes(column.dataIndex)">
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
import { cloneDeep } from 'lodash-es';
import { defineProps, reactive, toRefs, defineExpose } from 'vue';

const pagination = reactive({
  pageSizeOptions: ['10', '20', '30', '50'],
  showSizeChanger: true,
  defaultPageSize: 10,
});

const props = defineProps({
  initialData: Array
});

const columns = [
  {
    title: 'name',
    dataIndex: 'name',
    width: '20%',
  },
  {
    title: 'title',
    dataIndex: 'title',
    width: '25%',
  },
  {
    title: 'option',
    dataIndex: 'option',
    width: '40%',
  },
  {
    title: 'operation',
    dataIndex: 'operation',
  },
];

const dataSource = reactive(props.initialData);
const editableData: UnwrapRef<Record<string, DataItem>> = reactive({});

const edit = (key: string) => {
  console.log(key);
  editableData[key] = cloneDeep(dataSource.find(item => item.key === key));
};
const save = (key: string) => {
  Object.assign(dataSource.find(item => item.key === key), editableData[key]);
  delete editableData[key];
};
const cancel = (key: string) => {
  delete editableData[key];
};
defineExpose({
  edit,
});
</script>

<style scoped>
.editable-row-operations a {
  margin-right: 8px;
}
</style>
