import axios from 'axios'

export interface UserData {
  username?: string
  email: string
  password: string
  password_confirmation: string
}

export const Register = async (data: UserData) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/auth/register'
    const response = await axios.post(api, data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Registration Error:', error.response?.data)
      return {
        status: error.response?.status
      }
    } else {
      // 處理非 axios 錯誤
      console.error('Unexpected Error:', error)
    }
    throw error // 抛出錯誤，便於外部進一步處理
  }
}

export const Login = async (data: UserData) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/auth/login'
    const response = await axios.post(api, data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Login Error:', error.response?.data)
      return {
        status: error.response?.status
      }
    } else {
      // 處理非 axios 錯誤
      console.error('Unexpected Error:', error)
    }
    throw error // 抛出錯誤，便於外部進一步處理
  }
}

export const Logout = async () => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/auth/logout'
    const response = await axios.post(api, {
      headers: {
        Authorization: `Bearer ${localStorage.getItem('token')}`
      }
    })
    localStorage.removeItem('token')
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Logout Error:', error.response?.data)
      return {
        status: error.response?.status
      }
    } else {
      // 處理非 axios 錯誤
      console.error('Unexpected Error:', error)
    }
    throw error // 抛出錯誤，便於外部進一步處理
  }
}

export const fetchUserDataWithToken = async () => {
  const token = localStorage.getItem('token')
  const url = import.meta.env.VITE_BACKEND + 'api/profile/userprofile'

  try {
    const response = await axios.post(
      url,
      {},
      {
        headers: {
          Authorization: `Bearer ${token}`
        }
      }
    )
    return response.data
  } catch (error) {
    console.error('Error:', error)
    throw error // 可以选择抛出错误，也可以处理错误并返回一个默认值
  }
}
