import axios from 'axios';

export async function register(username: string, email: string, password: string) {
  const url = import.meta.env.VITE_BACKEND + '/auth/register';
  const response = await axios.post(url, {
    username,
    email,
    password,
  });
  return response.data;
}