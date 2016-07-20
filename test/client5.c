using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace SocketClient
{
    class Class1
    {
        [STAThread]
        static void Main(string[] args)
        {
            IPEndPoint server = new IPEndPoint(IPAddress.Parse("192.168.128.69"), 6000);
            UdpClient local = new UdpClient();
            local.Connect(server);

            Console.WriteLine("Client:");
            while (true)
            {
                string s = Console.ReadLine();
                byte[] data = Encoding.ASCII.GetBytes(s);

                local.Send(data, data.Length);
            }
        }
    }
}