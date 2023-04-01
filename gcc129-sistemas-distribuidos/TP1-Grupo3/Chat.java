import java.net.*;
import java.io.*;
import java.util.*;

public class Chat
{
    public static void main(String args[]) throws IOException, InterruptedException
    {
        //args[0] - ip address
        InetAddress ip = InetAddress.getByName(args[0]);

        //args[1] e args[2] - ports
        int sendPort = Integer.valueOf(args[1]);
        int receivePort = Integer.valueOf(args[2]);
        DatagramSocket ss = new DatagramSocket(receivePort);

        System.out.println("Chat rodando...");

        Thread ssend;
        ssend = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    Scanner sc = new Scanner(System.in);
                    while (true)
                    {
                        synchronized (this)
                        {
                            byte[] sd = new byte[1000];

                            sd = sc.nextLine().getBytes();
                            DatagramPacket sp = new DatagramPacket(sd, sd.length, ip, sendPort);

                            ss.send(sp);

                            String msg = new String(sd);

                            if (("bye").equals(msg))
                            {
                                System.out.println("Saindo...");
                                break;
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    System.out.println("Exception");
                }
            }
        });

        Thread sreceive;
        sreceive = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    while (true)
                    {
                        synchronized (this)
                        {
                            byte[] rd = new byte[1000];

                            // Receive new message
                            DatagramPacket sp1 = new DatagramPacket(rd, rd.length);
                            ss.receive(sp1);

                            // Convert byte data to string
                            String msg = (new String(rd)).trim();
                            System.out.println("User(" + sp1.getPort() + "):" + " " + msg);

                            // Exit condition
                            if ("bye".equals(msg))
                            {
                                System.out.println("Conexão fechada.");
                                break;
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    System.out.println("Exception");
                }
            }
        });

        ssend.start();
        sreceive.start();

        ssend.join();
        sreceive.join();
    }
}