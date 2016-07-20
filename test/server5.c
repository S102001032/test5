using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace SocketServer
{
 class Class1
 {
  [STAThread]
  static void Main(string[] args)
  {
   Socket udpServer = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.IP);
   IPEndPoint server = new IPEndPoint(IPAddress.Any, 6000);
   udpServer.Bind(server);
   
   Console.WriteLine("Server:");
   while(true)
   {
    byte[] buff = new byte[20];
    udpServer.Receive(buff);
    string s = Encoding.ASCII.GetString(buff, 0, buff.Length);
    Console.WriteLine(s);
    
   }
  }
 }
}