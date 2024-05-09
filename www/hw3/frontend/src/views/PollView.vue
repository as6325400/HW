<template>
  <a-layout style="min-height: 100vh">
    <a-layout-sider v-model:collapsed="collapsed" collapsible>
      <a-menu v-model:selectedKeys="selectedKeys" theme="dark" mode="inline">
        <a-sub-menu key="sub1">
          <template #title>
            <span>
              <user-outlined />
              <span>{{ username }}</span>
            </span>
          </template>
          <a-menu-item key="3">Home</a-menu-item>
          <a-menu-item key="4">Poll</a-menu-item>
        </a-sub-menu>
      </a-menu>
    </a-layout-sider>
    <a-layout>
      <a-layout-header style="background: #fff; padding: 0">
      
      </a-layout-header>
      <a-layout-content style="margin: 0 16px">
        <a-breadcrumb style="margin: 16px 0">
          <a-breadcrumb-item>用戶</a-breadcrumb-item>
          <a-breadcrumb-item>{{ username }}</a-breadcrumb-item>
        </a-breadcrumb>
        <div class="flex">
          <a-button type="primary" class="mx-4" @click="addEmptyRow">Primary Button</a-button>
          <a-input-search placeholder="搜索項目" v-model="searchQuery" style="margin-bottom: 16px" />
        </div>
        <!-- <a-table :columns="columns" :dataSource="filteredData" rowKey="id"></a-table> -->
        <PollTable ref="table" :initialData="data"/>
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Design ©2024 Created by Ant UED
      </a-layout-footer>
    </a-layout>
  </a-layout>
</template>

<script setup>
import { ref, computed } from 'vue'
import PollTable from '@/components/main/PollTable.vue'
const pollTableRef = ref(null);
const selectedKeys = ref([])
const searchQuery = ref('')
const username = ref('Username')
const collapsed = ref(false)
const table = ref(null)
import {
  PieChartOutlined,
  DesktopOutlined,
  UserOutlined,
  TeamOutlined,
  FileOutlined
} from '@ant-design/icons-vue'
let data = ref([
  {
    key: '1',
    name: 'John Brown',
    title: 32,
    option: 'New York No. 1 Lake Park',
  },
  {
    key: '2',
    name: 'Jim Green',
    title: 42,
    option: 'London No. 1 Lake Park',
  },
  {
    key: '3',
    name: 'Joe Black',
    title: 32,
    option: 'Sidney No. 1 Lake Park',
  },
]);
const addEmptyRow = () => {
  const newkey = `new-${data.value.length + 1}`
  data.value.unshift({
    key: newkey, // 給新行一個獨特的 key
    name: '',
    age: null,
    address: '',
  });
  table.value.edit(newkey);
};

</script>