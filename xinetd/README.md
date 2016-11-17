# xinetd

```bash
sudo apt-get install xinetd
# add xinetd config file
sudo cp /opt/linux-playground/xinetd/myserver /etc/xinetd.d/
# add a line for our myserver service to /etc/services
grep myserver /etc/services || echo -e "myserver\t9000/tcp" | sudo tee -a /etc/services
service xinetd restart
curl localhost:9000
```