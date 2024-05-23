import { createRouter, createWebHistory } from 'vue-router'
import MainView from '../views/MainView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'default',
      component: MainView
    },
    {
      path: '/main',
      name: 'main',
      component: MainView 
    },
    {
      path: '/:countyName/:year',
      name: 'town',
      component: () => import('../views/TownshipView.vue')
    }
  ]
})

export default router
