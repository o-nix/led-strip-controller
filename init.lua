function start(params)
  station_cfg = {}
  station_cfg.ssid = params.wifi_ssid
  station_cfg.pwd = params.wifi_password
  station_cfg.save = true

  wifi.setmode(wifi.STATION)
  wifi.sta.config(station_cfg)
  wifi.sta.sethostname("led-strip-controller")
  wifi.sta.autoconnect(1)

  wifi.sta.connect(function(ssid, bssid, channel)
    server = net.createServer(net.TCP, 300)

    function receiver(sck, data)
      uart.write(1, data)
    end

    if server then
      server:listen(22, function(conn)
        conn:on("receive", receiver)
      end)
    end
  end)
end

params_file = 'eus_params.lua'

function do_start()
  params = dofile(params_file)
  start(params)
end

if file.exists(params_file) then
  do_start()
else
  wifi.setmode(wifi.STATIONAP)
  wifi.ap.config({
    ssid = "LEDStripController",
    auth = wifi.OPEN })

  enduser_setup.manual(true)
  enduser_setup.start(function()
    do_start()
  end)
end