using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Cors;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace backend.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    
    public class AirConStatusController : ControllerBase
    {
        private const string dataFile = "./status.json";
        private AirConStatus _acStatus = JsonSerializer.Deserialize<AirConStatus>(System.IO.File.ReadAllText(dataFile));
        public AirConStatus acStatus
        {
            get
            {
                return _acStatus;
            }
            set
            {
                _acStatus = value;
                System.IO.File.WriteAllText(dataFile, JsonSerializer.Serialize<AirConStatus>(_acStatus));
            }
        }

        // GET: api/AirConStatus
        [HttpGet]
        public AirConStatus Get()
        {
            Console.WriteLine(string.Format("{0} Get AirConStatus",DateTime.Now));
            return acStatus;
        }

        // GET: api/AirConStatus/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/AirConStatus
        [HttpPost]
        public SendResult Post(AirConStatus value)
        {
            Console.WriteLine(string.Format("{0} Post AirConStatus", DateTime.Now));
            SendResult r1 = SendResult.CheckStatus(value);
            if (r1.Code != 0)
            {
                return r1;
            }

            acStatus = value;
            string exec_arg = string.Format("{0} {1} {2} {3} {4}",
                acStatus.Power, acStatus.Temperature, acStatus.Mode, acStatus.Swing, acStatus.WindSpeed);
            string stdOutput = "";

            try
            {
                Process proc = new Process();
                proc.StartInfo.FileName = "./irz";
                proc.StartInfo.Arguments = exec_arg;
                proc.StartInfo.UseShellExecute = false;
                proc.StartInfo.RedirectStandardOutput = true;
                proc.StartInfo.RedirectStandardError = true;
                proc.StartInfo.CreateNoWindow = true;
                proc.Start();
                proc.WaitForExit();
                stdOutput = proc.StandardOutput.ReadToEnd();
                string errOutput = proc.StandardError.ReadToEnd();
                proc.Close();
                if (stdOutput.Contains("Runtime Error") || stdOutput.Contains("failed") || errOutput.Contains("Error") || errOutput.Contains("Wrong"))
                {
                    return new SendResult(1, errOutput);
                }
                //Console.WriteLine(stdOutput);
                //Console.WriteLine("cerr: " + errOutput);
            }
            catch(Exception ex)
            {
                return new SendResult(1, ex.Message);
            }
            return new SendResult(0, stdOutput);
        }

        // PUT: api/AirConStatus/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE: api/ApiWithActions/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
