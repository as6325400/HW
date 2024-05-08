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
