#!/usr/bin/python2.7
import dpkt
import dpkt.tcp as tcp
from dpkt.tcp import TCP
import socket
import sys


def main():
    if (len(sys.argv) < 2):
        print "error: need argument"
        sys.exit(1)

    filename = sys.argv[1]
    print "input filename: " + filename
    f = open(filename)
    pcap = dpkt.pcap.Reader(f)
    #this is the dictionary that is going to hold everything that we need
    #will be in the form of a tuple so that the first value will have the number of syn connections and the second will ahve the number of syn + ack connections
    big_dict = {}
    for ts, buf in pcap:
        # we need to check the type of buf that we have
        try:
            eth = dpkt.ethernet.Ethernet(buf)
        except:
            continue
            #if it is not a ethernet then we will move on to the next element
        #another level of checking the right input
        if (type(eth.data) != dpkt.ip.IP):
            continue
        ip = eth.data

        if (type(eth.data.data) != dpkt.tcp.TCP):
            continue
        tcp = eth.data.data

        syn_flag = (tcp.flags & dpkt.tcp.TH_SYN) != 0
        ack_flag = (tcp.flags & dpkt.tcp.TH_ACK) != 0

        if syn_flag and ack_flag:
            if ip.dst not in big_dict:
                big_dict[ip.dst] = [0,1]
            else:
                big_dict[ip.dst][1] += 1

        elif syn_flag and (not ack_flag):
            if ip.src not in big_dict:
                big_dict[ip.src] = [1,0]
            else:
                big_dict[ip.src][0] += 1
    f.close()
    for key in big_dict:
        #checking the condition of if there is 3 times as many syn packets as syn + ack packets
        if big_dict[key][0] > (3*big_dict[key][1]):
            print socket.inet_ntoa(key)
    sys.exit(0)


if __name__ == '__main__':
    main()
