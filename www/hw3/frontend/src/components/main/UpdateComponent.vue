<template>
  <a-modal
    v-model:open="isModalVisible"
    title="Users Profile"
    @ok="handleOk"
    @cancel="handleCancel"
  >
    <a-form :model="profile" layout="vertical" class="profile-form">
      <div class="avatar-upload">
        <a-upload
          class="avatar-uploader border-none bg-transparent outline-none ring-0 opacity-100"
          list-type="picture-card"
          :show-upload-list="false"
          :before-upload="beforeUpload"
          @change="handleChange"
        >
          <div v-if="props.imgpath" class="avatar-wrapper">
            <a-avatar :src="props.imgpath" :size="192" />
          </div>
          <div v-else class="avatar-uploader-trigger">
            <a-avatar class="h-full w-full absolute" :size="192">
              <template #icon><UserOutlined /></template>
            </a-avatar>
          </div>
          <div class="h-full w-full upload-trigger absolute top-0 left-0 z-2 flex justify-center items-center">
            <span>Click to upload</span>
          </div>
        </a-upload>
      </div>
      <a-segmented v-model:value="value" block :options="data" />
      <div v-show="showPhoto">
        <a-form-item label="Username">
          <a-input
            v-model:value="profile.username"
            placeholder="Username"
            autocomplete="new-password"
          />
        </a-form-item>
        <a-form-item label="Password">
          <a-input
            type="password"
            v-model:value="profile.password"
            placeholder="Password"
            autocomplete="new-password"
          />
        </a-form-item>
      </div>
      <div v-show="!showPhoto">
        <a-form-item label="Username">
          <a-input v-model:value="profile.username" placeholder="Username" autocomplete="new-password" />
        </a-form-item>
        <a-form-item label="New Password">
          <a-input
            type="password"
            v-model:value="profile.newPassword"
            placeholder="New Password"
            autocomplete="new-password"
          />
        </a-form-item>
        <a-form-item label="Confirm New Password">
          <a-input
            type="password"
            v-model:value="profile.confirmNewPassword"
            placeholder="Confirm New Password"
            autocomplete="new-password"
          />
        </a-form-item>
        <a-form-item label="Current Password">
          <a-input
            type="password"
            v-model:value="profile.oldPassword"
            placeholder="Current Password"
            autocomplete="new-password"
          />
        </a-form-item>
      </div>
    </a-form>
  </a-modal>
</template>
<script setup>
import { ref, reactive, watch } from 'vue'
import { UserOutlined } from '@ant-design/icons-vue'
import { Modal, Form, Input, Upload, Avatar } from 'ant-design-vue'
import { uploadimg, updatePassword } from '@/functions/user'

const isModalVisible = ref(false)
const showPhoto = ref(true)
const profile = ref({
  username: '',
  password: '',
  confirmPassword: '',
  oldPassword: '',
  newPassword: '',
  confirmNewPassword: '',
})

const props = defineProps({
  imgpath: {
    type: String,
    default: null
  },
  username: {
    type: String,
    default: 'Username'
  }
})

const data = reactive(['Photo', 'Password'])
const value = ref(data[0])
watch(value, (val) => {
  if (val === 'Photo') {
    showPhoto.value = true
    console.log('Photo')
  } else {
    showPhoto.value = false
    console.log('Password')
  }
})

watch(
  () => props.username,
  (val) => {
    console.log('props.username', val)
    if (val) {
      profile.value.username = val
    }
  }
)

const emit = defineEmits(['handleOk', 'handleCancel'])

async function handleOk() {
  if (showPhoto.value) {
    if (!profile.value.photo) {
      alert('Please upload a photo')
      return
    }
    if (!profile.value.username) {
      console.log(profile.value.username)
      alert('Please enter a username')
      return
    }
    if (!profile.value.password) {
      alert('Please enter a password')
      return
    }
    const response = await uploadimg(
      profile.value.username,
      profile.value.password,
      profile.value.photo
    )
    console.log('Uploading photo...', response)
  } else {
    console.log('profile.value', profile.value

    )
    if (!profile.value.username) {
      alert('Please enter a username')
      return
    }
    if (!profile.value.oldPassword) {
      alert('Please enter your current password')
      return
    }
    if (!profile.value.newPassword) {
      alert('Please enter a new password')
      return
    }
    if (!profile.value.confirmNewPassword) {
      alert('Please confirm your new password')
      return
    }
    if (profile.value.newPassword !== profile.value.confirmNewPassword) {
      alert('New password and confirm password do not match')
      return
    }
    console.log('Changing password...')
    const response = await updatePassword(
      profile.value.username,
      profile.value.oldPassword,
      profile.value.newPassword
    )
  }
  isModalVisible.value = false
  console.log(isModalVisible.value)
  window.location.href = '/home'
}

function handleCancel() {
  console.log(isModalVisible.value)
  isModalVisible.value = false
  window.location.href = '/home'
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
  return false
}

function handleChange({ file }) {
  const imageData = ref(null)
  if (file && file.type.startsWith('image')) {
    const reader = new FileReader()
    reader.onload = (e) => {
      imageData.value = e.target.result // 將讀取到的資料 URL 賦值給 imageData
      profile.value.photo = imageData.value // 存儲文件對象到 ref 變量
    }
    reader.readAsDataURL(file) // 讀取文件作為資料 URL
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
  background-color: rgba(255, 255, 255, 0.5);
}
.avatar-uploader:hover .upload-trigger {
  opacity: 1; /* 悬停时显示 */
}
</style>
