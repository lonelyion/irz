using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace backend
{
    public class SendResult
    {
        [JsonPropertyName("code")]
        public int Code { get; set; }
        [JsonPropertyName("message")]
        public string Message { get; set; }

        public SendResult(int c, string msg)
        {
            Code = c;
            Message = msg;
        }

        public static SendResult CheckStatus(AirConStatus status)
        {
            if (status.Power != 0 && status.Power != 1)
            {
                return new SendResult(1, "Power value is not valid");
            }
            if(status.Temperature < 16 || status.Temperature > 31)
            {
                return new SendResult(1, "Temperature value must be in [16, 32)");
            }
            if(status.Mode < 0 || status.Mode > 2)
            {
                return new SendResult(1, "Mode value is not valid");
            }
            if(status.Swing != 0 && status.Swing != 1)
            {
                return new SendResult(1, "Swing value is not valid");
            }
            if(status.WindSpeed < 0 || status.WindSpeed > 3)
            {
                return new SendResult(1, "Wind Speed value is not valid");
            }

            return new SendResult(0, "");
        }
    }
}
