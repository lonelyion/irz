<template>
  <v-container fluid>
    <v-layout wrap>
      <v-card class="mx-auto">
        <v-card-title>Power</v-card-title>
        <v-card-text>电源开关</v-card-text>
        <v-card-actions>
          <v-btn icon>
            <v-icon color="cyan">fa-plug</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon>fa-power-off</v-icon>
          </v-btn>
        </v-card-actions>
      </v-card>
      <v-card  class="mx-auto" >
        <v-card-title>Temperature</v-card-title>
        <v-card-text>
          <p>当前目标温度</p>
          <span class="display-2 font-weight-light indigo--text">24</span>
          <span class="subheading font-weight-light mr-1">℃</span>
        </v-card-text>
        <v-card-actions>
          <v-btn icon>
            <v-icon>fa-chevron-up</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon>fa-chevron-down</v-icon>
          </v-btn>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto" >
        <v-card-title>Mode</v-card-title>
        <v-card-text>设置空调模式</v-card-text>
        <v-card-actions>
          <v-btn icon>
            <v-icon color="light-blue">fa-snowflake</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon>fa-sun</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon>fa-tint</v-icon>
          </v-btn>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto">
        <v-card-title>Wind Speed</v-card-title>
        <v-card-text>调节风速大小</v-card-text>
        <v-card-actions>
          <v-btn text color="deep-purple accent-4">Auto</v-btn>
          <v-btn text>1</v-btn>
          <v-btn text>2</v-btn>
          <v-btn text>3</v-btn>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto">
        <v-card-title>Wings Direction</v-card-title>
        <v-card-text>调节风向</v-card-text>
        <v-card-actions>
          <v-btn icon>
            <v-icon color="indigo">fa-thumbtack</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon>fa-arrows-alt-v</v-icon>
          </v-btn>
        </v-card-actions>
      </v-card>
    </v-layout>
  </v-container>
</template>

<script>
  export default {
      data: {
          ac_status: []
      },
      created: function () {

      }
  }
</script>

<style scoped>
  .v-card {
    width: 419px;
    margin-bottom: 16px;
  }
</style>
