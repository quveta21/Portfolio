import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'ESP32 BLE Connect',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        useMaterial3: true,
      ),
      debugShowCheckedModeBanner: false,
      home: const DeviceScreen(),
    );
  }
}

class DeviceScreen extends StatefulWidget {
  const DeviceScreen({super.key});

  @override
  State<DeviceScreen> createState() => _DeviceScreenState();
}

class _DeviceScreenState extends State<DeviceScreen> {
  BluetoothDevice? _connectedDevice;
  final List<BluetoothDevice> _devices = []; // setNotifyValue
  bool _isScanning = false;
  String _status = "Tap 'Scan' to begin";
  StreamSubscription<List<ScanResult>>? _scanSubscription;

  // UUIDs must match ESP32 code
  static const String serviceUuid = "0000abcd-0000-1000-8000-00805f9b34fb";
  static const String rxCharUuid = "0000beef-0000-1000-8000-00805f9b34fb"; // RX on ESP32
  static const String txCharUuid = "0000deaf-0000-1000-8000-00805f9b34fb"; // TX from ESP32
  String dist = "-1.0";
  @override
  void dispose() {
    _scanSubscription?.cancel();
    _connectedDevice?.disconnect();
    super.dispose();
  }

  void _startScan() {
    setState(() {
      _isScanning = true;
      _devices.clear();
      _status = "Scanning...";
    });

    _scanSubscription?.cancel();
    _scanSubscription = FlutterBluePlus.scanResults.listen((results) {
      for (final result in results) {
        if (result.device.name == "ESP32_BLE") {
          if (!_devices.any((d) => d.remoteId == result.device.remoteId)) {
            setState(() {
              _devices.add(result.device);

              _status = "Found ${_devices.length} devices";
            });
          }
        }
      }
    }, onError: (e) {
      setState(() => _status = "Scan error: ${e.toString()}");
    });

    FlutterBluePlus.startScan(
      timeout: const Duration(seconds: 10),
      androidUsesFineLocation: false,
    );
  }

  Future<void> _sendMamaliga(BluetoothCharacteristic characteristic) async {
    try {
      print("adaug aicea");
      await characteristic.write("blink".codeUnits);
      if (mounted) {
        setState(() => _status = "Sent: blink");
      }
    } catch (e) {
      if (mounted) {
        setState(() => _status = "Send failed: ${e.toString()}");
      }
    }
  }

  Future<void> _getDistData(BluetoothCharacteristic characteristic) async{
    try {
      print("cer aicea");
      List<int> value = List.empty();

      if (characteristic.properties.read) {
        // Safe to read
        value = await characteristic.read();
        print("Read: ${String.fromCharCodes(value)}");
        // reads great
        dist = String.fromCharCodes(value);
      }
      else{
        setState(() => _status = "Nu i voie citire");
      }

      if (mounted) {

        setState(() => _status = "Received: $dist");
      }
    } catch (e) {
      if (mounted) {
        setState(() => _status = "Receive failed: ${e.toString()}");
      }
    }

  }
  String getFullUuid(Guid guid) {
    // Convert to full 128-bit UUID format
    return guid.toString().toLowerCase(); // Returns full UUID like "0000abcd-0000-1000-8000-00805f9b34fb"
  }

  Future<String> getPlatformUuid(Guid guid) async {
    const channel = MethodChannel('flutter_blue_plus/methods');
    try {
      final result = await channel.invokeMethod('getFullUuid', guid.toString());
      return result;
    } on PlatformException catch (e) {
      return guid.toString(); // Fallback
    }
  }

  Future<void> _connectToDevice(BluetoothDevice device) async {
    try {

      setState(() => _status = "Connecting...");
      await device.connect(autoConnect: false);

      setState(() {
        _connectedDevice = device;
        _status = "Connected to ${device.name}";

      });

      final services = await device.discoverServices();

      for (BluetoothService service in services) {


        if (service.uuid.toString().compareTo("abcd") == 0) {


          for (final characteristic in service.characteristics) {

            if (characteristic.uuid.toString() == rxCharUuid) {
              // Send "mamaliga" immediately after connecting
              await _sendMamaliga(characteristic);

            }
            await _sendMamaliga(characteristic);
            await _getDistData(characteristic);
            if (characteristic.uuid.toString() == txCharUuid) {
              await characteristic.setNotifyValue(true);
              await _sendMamaliga(characteristic);
              characteristic.value.listen((value) {
                final message = String.fromCharCodes(value);
                if (mounted) {
                  setState(() => _status = "Received: $message");
                }
              });
            }
          }
        }
      }
    } catch (e) {
      if (mounted) {
        setState(() => _status = "Connection failed: ${e.toString()}");
      }
      await device.disconnect();
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('ESP32 BLE Connect'),
        actions: [
          if (_isScanning)
            const Padding(
              padding: EdgeInsets.all(12.0),
              child: CircularProgressIndicator(
                strokeWidth: 2,
                valueColor: AlwaysStoppedAnimation(Colors.white),
              ),
            ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            Card(
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Text(
                  _status,
                  style: Theme.of(context).textTheme.titleMedium,
                  textAlign: TextAlign.center,
                ),
              ),
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed:  _startScan,
              child: const Text('Scan for Devices'),

            ),
            const SizedBox(height: 20),
            Expanded(
              child: _devices.isEmpty
                  ? const Center(child: Text("No devices found"))
                  : ListView.builder(
                itemCount: _devices.length,
                itemBuilder: (context, index) {
                  final device = _devices[index];

                  return Card(
                    child: ListTile(
                      title: Text(device.name ?? "Unknown Device"),
                      subtitle: Text(device.remoteId.toString()),

                      trailing: _connectedDevice?.remoteId == device.remoteId
                          ? const Icon(Icons.bluetooth_connected)
                          : null,
                      onTap: () => _connectToDevice(device),
                    ),
                  );
                },
              ),
            ),
            Card(
    child: ListTile(
                title: dist.compareTo("-1.0") != 0 ? Text(dist) : null),
            ),

          ],
        ),
      ),
    );
  }
}