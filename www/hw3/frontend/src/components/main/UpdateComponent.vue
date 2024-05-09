<template>
  <a-modal
    v-model:visible="isModalVisible"
    title="Users Profile"
    @ok="handleOk"
    @cancel="handleCancel"
  >
    <a-form :model="profile" layout="vertical" class="profile-form">
      <div class="avatar-upload">
        <a-upload
          class="avatar-uploader border-none bg-transparent outline-none ring-0"
          list-type="picture-card"
          :show-upload-list="false"
          :before-upload="beforeUpload"
          @change="handleChange"
        >
          <div v-if="profile.photo" class="avatar-wrapper">
            <a-avatar :src="profile.photo" :size="192" />
            <!-- <div class="avatar-uploader-trigger">Click to upload</div> -->
          </div>
          <div v-else class="avatar-uploader-trigger">
            <a-avatar :src="img" class="h-full w-full absolute" :size="192">
              <template #icon><UserOutlined /></template>
            </a-avatar>
            <span class="upload-trigger absolute z-2">Click to upload</span>
          </div>
        </a-upload>
      </div>
      <a-segmented v-model:value="value" block :options="data" />
      <div v-if="showPhoto">
        <a-form-item label="Username">
          <a-input v-model="profile.username" placeholder="Username" autocomplete="new-password"/>
        </a-form-item>
        <a-form-item label="Password">
          <a-input type="password" v-model="profile.password" placeholder="Password" autocomplete="new-password"/>
        </a-form-item>
        <a-form-item label="Confirm Password">
          <a-input type="password" v-model="profile.confirmPassword" placeholder="Confirm Password" autocomplete="new-password"/>
        </a-form-item>
      </div>
      <div v-else>
        <a-form-item label="Username">
          <a-input v-model="profile.username" placeholder="Username" autocomplete="new-password"/>
        </a-form-item>
        <a-form-item label="New Password">
          <a-input type="password" v-model="profile.password" placeholder="Password" autocomplete="new-password"/>
        </a-form-item>
        <a-form-item label="Confirm New Password">
          <a-input type="password" v-model="profile.confirmPassword" placeholder="Confirm Password" autocomplete="new-password"/>
        </a-form-item>
        <a-form-item label="Current Password">
          <a-input type="password" v-model="profile.password" placeholder="Password" autocomplete="new-password"/>
        </a-form-item>
      </div>
    </a-form>
  </a-modal>
</template>
<script setup>
import { ref, reactive, watch } from 'vue'
import { UserOutlined } from '@ant-design/icons-vue'
import { Modal, Form, Input, Upload, Avatar } from 'ant-design-vue'
import img from './images.jpeg' // Make sure the filename here matches your image file name
const isModalVisible = ref(false)
const showPhoto = ref(true)
const profile = ref({
  username: '',
  password: '',
  confirmPassword: '',
  photo: null
})
const data = reactive(['Photo', 'Password']);
const value = ref(data[0]);
watch(value, (val) => {
  if (val === 'Photo') {
    showPhoto.value = true
    console.log('Photo')
  }
  else{
    showPhoto.value = false
    console.log('Password')
  }
})
function handleOk() {
  console.log('Submitted:', profile.value)
  isModalVisible.value = false
}

function handleCancel() {
  isModalVisible.value = false
}

function beforeUpload(file) {
  console.log('beforeUpload', file)
  // 获取文件名并转换为小写，以便比较
  const fileName = file.name.toLowerCase()
  const isValidExtension =
    fileName.endsWith('.png') || fileName.endsWith('.jpg') || fileName.endsWith('.jpeg')

  if (!isValidExtension) {
    alert('You can only upload image files with extensions .png, .jpg, or .jpeg!')
    return false 
  }
  return true 
}

function handleChange({ file }) {
  if (file.status === 'done') {
    // Assuming the response from server includes the url of the image
    profile.value.photo = file.response.url
  }
}
</script>

<style scoped>
.avatar-uploader .ant-upload:focus {
  outline: none !important;
  border: none !important;
  box-shadow: none !important;
}
.avatar-upload {
  display: flex;
  justify-content: center;
  margin-bottom: 20px;
  border-width: none;
}
.avatar-uploader {
  width: 192px;
  height: 192px;
  border-radius: 50%;
  overflow: hidden;
  position: relative;
}
.avatar-wrapper {
  position: relative;
  width: 100%;
  height: 100%;
  border-radius: 50%;
}
.avatar-uploader-trigger {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100%;
  width: 100%;
  position: absolute;
  top: 0;
  left: 0;
  background-color: rgba(255, 255, 255, 0.5); /* 設定半透明覆蓋層 */
  border-radius: 50%;
  opacity: 0;
  transition: opacity 0.3s;
  opacity: 1;
}
.avatar-uploader-trigger:hover {
  opacity: 0.7; /* hover 時顯示覆蓋層 */
}
.upload-trigger {
  opacity: 0; /* 默认不显示 */
  transition: opacity 0.3s ease; /* 平滑过渡效果 */
}
.avatar-uploader:hover .upload-trigger {
  opacity: 1; /* 悬停时显示 */
}
</style>
