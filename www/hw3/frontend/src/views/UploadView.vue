<template>
  <a-space direction="vertical" :size="32">
    <a-space wrap :size="16">
      <a-avatar :size="64">
        <template #icon><UserOutlined /></template>
      </a-avatar>
    </a-space>
  </a-space>
</template>
<script lang="ts" setup>
import { UserOutlined } from '@ant-design/icons-vue';
</script>

