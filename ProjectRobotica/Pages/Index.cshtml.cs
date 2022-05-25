using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;


namespace ProjectRobotica.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ILogger<IndexModel> _logger;

        public static string data = null;
        public static string[] s2;

        public IndexModel(ILogger<IndexModel> logger)
        {
            _logger = logger;
        }

        public string weight = "0";
        public string RPM = "0";

        public static IPAddress ipAddress;
        public static IPEndPoint localEndPoint;
        public static Socket listener;

        public void OnGet()
        {
            IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            ipAddress = ipHostInfo.AddressList[3];
            localEndPoint = new IPEndPoint(ipAddress, 11000);
            System.Console.Write(ipAddress);
            listener = new Socket(ipAddress.AddressFamily,
                SocketType.Stream, ProtocolType.Tcp);
            listener.Bind(localEndPoint);
        }

        public void OnPostServer()
        {

            // Data buffer for incoming data.  
            byte[] bytes = new Byte[1024];

            // Establish the local endpoint for the socket.  
            // Dns.GetHostName returns the name of the
            // host running the application.  
            

            // Create a TCP/IP socket.  
            

            // Bind the socket to the local endpoint and
            // listen for incoming connections.  
            try
            {
                
                listener.Listen(10);

                // Start listening for connections.  

                Console.WriteLine("Waiting for a connection...");
                // Program is suspended while waiting for an incoming connection.  
                Socket handler = listener.Accept();
                data = null;

                // An incoming connection needs to be processed.  
                while (true)
                {
                    int bytesRec = handler.Receive(bytes);
                    data += Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    if (data.IndexOf("<EOF>") > -1)
                    {
                        break;
                    }
                }

                // Show the data on the console.  
                s2 = data.Split(',');
                for (int i = 0; i < (s2.Length - 1); i++)
                {
                    Console.WriteLine("Text received : {0}", s2[i]);
                }

                weight = s2[0];
                RPM = s2[1];
             

                // Echo the data back to the client.  
                byte[] msg = Encoding.ASCII.GetBytes(data);

                handler.Send(msg);
                handler.Shutdown(SocketShutdown.Both);
                handler.Close();

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            //Console.WriteLine("\nPress ENTER to continue...");
            //Console.Read();
        }

        public void OnPostReset()
        {
            weight = "0";
            RPM = "0";

            
        }
    }
}
