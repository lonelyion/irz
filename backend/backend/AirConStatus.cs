using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace backend
{
    public class AirConStatus
    {
        [JsonPropertyName("power")]
        public int Power { get; set; }
        [JsonPropertyName("temperature")]
        public int Temperature { get; set; }
        [JsonPropertyName("mode")]
        public int Mode { get; set; }
        [JsonPropertyName("swing")]
        public int Swing { get; set; }
        [JsonPropertyName("windspeed")]
        public int WindSpeed { get; set; }

    }
}
