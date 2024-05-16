import axios from 'axios'

export const CreateVote = async (topic: string, title: string, options: string[]) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/vote/createvote'
    const token = localStorage.getItem('token')
    const response = await axios.post(
      api,
      {
        topic: topic,
        title: title,
        options: options
      },
      {
        headers: {
          Authorization: `Bearer ${token}`
        }
      }
    )
    console.log('Create Vote:', response.data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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

export const EditVote = async (topic: string, title: string, options: string[]) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/vote/editvote'
    const token = localStorage.getItem('token')
    const response = await axios.post(
      api,
      {
        topic: topic,
        title: title,
        options: options
      },
      {
        headers: {
          Authorization: `Bearer ${token}`
        }
      }
    )
    console.log('Edit Vote:', response.data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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

export const DeleteVote = async (topic: string, title: string) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/vote/deletevote'
    const token = localStorage.getItem('token')
    const response = await axios.post(
      api,
      {
        topic: topic,
        title: title
      },
      {
        headers: {
          Authorization: `Bearer ${token}`
        }
      }
    )
    console.log('Delete Vote:', response.data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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

export const gettime = async (topic: string, title: string) => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/vote/gettime'
    const response = await axios.post(api, {
      topic: topic,
      title: title
    })
    console.log('Get Time:', response.data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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

export const getAllVotes = async () => {
  try {
    const api = import.meta.env.VITE_BACKEND + 'api/vote/getallvotes'
    const response = await axios.post(api)
    console.log('Get All Vote:', response.data)
    return response
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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

export const getVote = async (topic_id: string, option_id: number, username: string) => {
  try {
    const token = localStorage.getItem('token')
    const api = import.meta.env.VITE_BACKEND + 'api/vote/getvote'
    const response = await axios.post(
      api,
      {
        topic_id: topic_id,
        option_id: option_id,
        username: username
      },
      {
        headers: {
          Authorization: `Bearer ${token}`
        }
      }
    )
    console.log('Get Vote:', response.data)
  } catch (error) {
    if (axios.isAxiosError(error)) {
      // 處理 axios 錯誤
      console.error('Vote Error:', error.response?.data)
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
