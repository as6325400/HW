import axios from "axios";



export async function getdata(area: string, time: string) {
  const data = JSON.stringify({
    "area": area,
    "year": time
  });

  const config = {
    method: 'post',
    maxBodyLength: Infinity,
    url: 'http://wwweb2024.csie.io:52000/api.php',
    headers: { 
      'Authorization': 'Token h6kcdm9pazx7j9xd',
      'Content-Type': 'application/json'
    },
    data: data
  };
  
  try {
    const response = await axios.request(config);
    return response.data;
  } catch (error) {
    console.error(error);
    throw error; 
  }
}