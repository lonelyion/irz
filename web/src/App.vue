<template>
  <v-app id="inspire">
    <v-navigation-drawer
            v-model="drawer"
            app
    >
      <v-list dense>
        <v-list-item @click="">
          <v-list-item-action>
          <v-icon>fa-link</v-icon>
          </v-list-item-action>
          <v-list-item-content>
            <v-list-item-title>遥控器</v-list-item-title>
          </v-list-item-content>
        </v-list-item>
        <v-list-item @click="">
          <v-list-item-action>
            <v-icon>fa-thermometer</v-icon>
          </v-list-item-action>
          <v-list-item-content>
            <v-list-item-title>室内温湿度(WIP)</v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>

    <v-app-bar
            app
            color="blue"
            dark
    >
      <v-app-bar-nav-icon @click.stop="drawer = !drawer"></v-app-bar-nav-icon>
      <v-toolbar-title>402 AirCon Control</v-toolbar-title>
      <div class="flex-grow-1"></div>
      <v-btn icon>
        <v-icon>fa-paper-plane</v-icon>
      </v-btn>
    </v-app-bar>

    <v-content>
      <HelloWorld></HelloWorld>
    </v-content>
    <v-footer
            color="indigo"
            app
    >
      <span class="white--text">Made with <span class="pink--text">♥</span> and 🌽 by Copper</span>
    </v-footer>
  </v-app>
</template>

<script>
    import HelloWorld from './components/HelloWorld.vue'

    export default {
        components: {
            HelloWorld
        },
        props: {
            source: String,
        },
        data: () => ({
            drawer: null,
        }),
    }
</script>

<style>
  .v-application {
    font-family: 'Noto Sans SC', 'Roboto', 'Microsoft YaHei UI', sans-serif !important;
  }
</style>
