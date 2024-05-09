<template>
  <a-layout style="min-height: 100vh">
    <a-layout-sider v-model:collapsed="collapsed" collapsible>
      <div class="logo" />
      <a-menu v-model:selectedKeys="selectedKeys" theme="dark" mode="inline">
        <a-menu-item key="1">
          <a-icon type="user" />
          <span>首頁</span>
        </a-menu-item>
        <a-menu-item key="2">
          <a-icon type="video-camera" />
          <span>視頻</span>
        </a-menu-item>
        <a-menu-item key="3">
          <a-icon type="upload" />
          <span>上傳</span>
        </a-menu-item>
        <a-sub-menu key="sub1">
          <template #title>
            <a-icon type="user" />
            <span>用戶</span>
          </template>
          <a-menu-item key="4">Tom</a-menu-item>
          <a-menu-item key="5">Bill</a-menu-item>
        </a-sub-menu>
      </a-menu>
    </a-layout-sider>
    <a-layout>
      <a-layout-header style="background: #fff; padding: 0">
        <a-icon type="menu-fold" @click="collapsed = !collapsed" style="margin: 16px" />
        <div style="float: right; padding: 0 16px 0 0">
          <a-dropdown>
            <a class="ant-dropdown-link" @click="e => e.preventDefault()">
              {{ username }} <a-icon type="down" />
            </a>
            <a-menu slot="overlay">
              <a-menu-item key="1">個人中心</a-menu-item>
              <a-menu-item key="2">登出</a-menu-item>
            </a-menu>
          </a-dropdown>
        </div>
      </a-layout-header>
      <a-layout-content style="margin: 0 16px">
        <a-breadcrumb style="margin: 16px 0">
          <a-breadcrumb-item>用戶</a-breadcrumb-item>
          <a-breadcrumb-item>{{ username }}</a-breadcrumb-item>
        </a-breadcrumb>
        <a-input-search placeholder="搜索項目" v-model="searchQuery" style="margin-bottom: 16px" />
        <a-table :columns="columns" :dataSource="filteredData" rowKey="id"></a-table>
      </a-layout-content>
      <a-layout-footer style="text-align: center">
        Design ©2024 Created by Ant UED
      </a-layout-footer>
    </a-layout>
  </a-layout>
</template>
