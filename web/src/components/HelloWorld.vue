<template>
  <v-container fluid>
    <v-layout wrap>
      <v-row justify="center">
        <v-dialog max-width="290" persistent v-model="dialog">
          <v-card>
            <v-card-title class="headline">哦豁，出错了</v-card-title>
            <v-card-text>{{ error_message }}</v-card-text>
            <v-card-actions>
              <v-spacer></v-spacer>
              <v-btn @click="dialog = false" color="green darken-1" text>那咋办嘛？</v-btn>
            </v-card-actions>
          </v-card>
        </v-dialog>
      </v-row>
      <v-card class="mx-auto">
        <v-card-title>Power</v-card-title>
        <v-card-text>电源开关</v-card-text>
        <v-card-actions>
          <v-btn-toggle borderless color="transparent" dense mandatory tile v-model="ac_status.power">
            <v-btn icon>
              <v-icon :color="ac_status.power === 0 ? 'red' : null">fa-power-off</v-icon>
            </v-btn>
            <v-btn icon>
              <v-icon :color="ac_status.power === 1 ? 'cyan' : null">fa-plug</v-icon>
            </v-btn>
          </v-btn-toggle>
        </v-card-actions>
      </v-card>
      <v-card  class="mx-auto" >
        <v-card-title>Temperature</v-card-title>
        <v-card-text>
          <p>当前目标温度</p>
          <span class="display-2 font-weight-light indigo--text">{{ ac_status.temperature }}</span>
          <span class="subheading font-weight-light mr-1"> ℃</span>
        </v-card-text>
        <v-card-actions>
          <v-btn @click="change_temp('plus')" icon>
            <v-icon>fa-chevron-up</v-icon>
          </v-btn>
          <v-btn @click="change_temp('minus')" icon>
            <v-icon>fa-chevron-down</v-icon>
          </v-btn>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto" >
        <v-card-title>Mode</v-card-title>
        <v-card-text>设置空调模式</v-card-text>
        <v-card-actions>
          <v-btn-toggle borderless color="transparent" dense mandatory tile v-model="ac_status.mode">
          <v-btn icon>
            <v-icon :color="ac_status.mode === 0 ? 'light-blue' : null">fa-snowflake</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon :color="ac_status.mode === 1 ? 'orange' : null">fa-sun</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon :color="ac_status.mode === 2 ? 'lime' : null">fa-tint</v-icon>
          </v-btn>
          </v-btn-toggle>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto">
        <v-card-title>Wind Speed</v-card-title>
        <v-card-text>调节风速大小</v-card-text>
        <v-card-actions>
          <v-btn-toggle borderless color="transparent" dense mandatory tile v-model="ac_status.windspeed">
          <v-btn :color="ac_status.windspeed === 0 ? 'deep-purple' : null" text>Auto</v-btn>
          <v-btn :color="ac_status.windspeed === 1 ? 'deep-purple darken-1' : null" text>1</v-btn>
          <v-btn :color="ac_status.windspeed === 2 ? 'deep-purple darken-2' : null" text>2</v-btn>
          <v-btn :color="ac_status.windspeed === 3 ? 'deep-purple darken-3' : null" text>3</v-btn>
          </v-btn-toggle>
        </v-card-actions>
      </v-card>
      <v-card class="mx-auto">
        <v-card-title>Wings Direction</v-card-title>
        <v-card-text>调节风向</v-card-text>
        <v-card-actions>
          <v-btn-toggle borderless color="transparent" dense mandatory tile v-model="ac_status.swing">
          <v-btn icon>
            <v-icon :color="ac_status.swing === 0 ? 'indigo' : null">fa-thumbtack</v-icon>
          </v-btn>
          <v-btn icon>
            <v-icon :color="ac_status.swing === 1 ? 'indigo' : null">fa-arrows-alt-v</v-icon>
          </v-btn>
          </v-btn-toggle>
        </v-card-actions>
      </v-card>
    </v-layout>
  </v-container>
</template>

<script>
    const axios = require('axios').default;

  export default {
      data: function() {
          return {
              url: 'https://acback.copperion.com',
              ac_status: null,
              error_message: null,
              ac_response: null,
              ax_error: null,
              dialog: false
          }
      },

      watch: {
          ac_status: {
              handler (val, oldVal) {
                  if(oldVal != null) {
                      axios.post(this.url + '/api/AirConStatus', val)
                          .then(res => (this.ac_response = res.data))
                          .catch(err => (this.ax_error = err));
                      if(this.ax_error != null) {
                          this.show_error("在POST时出现了一点毛病。" + this.ax_error);
                          this.ax_error = null;
                          return;
                      }
                      if(this.ac_response.code === 1) {
                          this.show_error("在POST后发送红外信号时出了一点小小的问题。" + this.ac_response.message);
                      }
                  }
              },
              deep: true
          }
      },

      mounted: function () {
          axios.get(this.url + '/api/AirConStatus')
              .then(response => (this.ac_status = response.data))
              .catch(err => (this.ax_error = err));

          if(this.ax_error != null) {
              this.show_error("在GET请求的时候出问题了，大概率接下来什么也不能用。");
              this.ax_error = null;
          }
      },

      methods: {
          change_temp: function (op) {
              if(op === 'plus') {
                  if(this.ac_status.temperature < 31) {
                      this.ac_status.temperature++;
                  }
              }
              else if(op === 'minus') {
                  if(this.ac_status.temperature > 16) {
                      this.ac_status.temperature--;
                  }
              }
          },
          show_error(message) {
              this.error_message = message;
              this.dialog = true;
          }
      }

  }

</script>

<style scoped>
  .v-card {
    width: 419px;
    margin-bottom: 16px;
  }
</style>
