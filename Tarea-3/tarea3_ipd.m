
puerto = 'COM3'; 
baudrate = 115200;

try
    s = serialport(puerto, baudrate, "Parity", "Even", "DataBits", 8, "StopBits", 1);
    flush(s);

    write(s, hex2dec('7F'), "uint8");
    
    ack = read(s, 1, "uint8");
    if isempty(ack) || ack ~= hex2dec('79') % Verificar ACK 0x79 
        error('Fallo en la sincronización.');
    end
    disp('ACK recibido');

    cmd_read = [hex2dec('11'), hex2dec('EE')]; 
    write(s, cmd_read, "uint8");
    
    ack = read(s, 1, "uint8");
    if ack ~= hex2dec('79')
        error('Error en read memory');
    end

    dir_bytes = [hex2dec('08'), hex2dec('00'), hex2dec('00'), hex2dec('00')]; %dirección de memoria
    
    checksum_dir = bitxor(bitxor(bitxor(dir_bytes(1), dir_bytes(2)), dir_bytes(3)), dir_bytes(4));
    
    write(s, [dir_bytes, checksum_dir], "uint8");
    
    ack = read(s, 1, "uint8");
    if ack ~= hex2dec('79')
        error('error en dirección de memoria');
    end

    N = hex2dec('FF'); %cantidad de bytes a leer
    checksum_N = bitcmp(N, 'uint8'); % Complemento a 1
    
    write(s, [N, checksum_N], "uint8");
    
    ack = read(s, 1, "uint8");
    if ack ~= hex2dec('79')
        error('error en cantidad de bytes');
    end

    datos_flash = read(s, 256, "uint8");
    
    if length(datos_flash) == 256
        disp('Lectura exitosa');
        
        fileID = fopen('lectura_flash_stm32.txt', 'w');
        fprintf(fileID, 'Memoria Flash Inicio: 0x08000000\n\n');

        for i = 1:16:256
            linea_hex = sprintf('%02X ', datos_flash(i:min(i+15, 256)));
            fprintf(fileID, '0x0800%04X: %s\n', i-1, linea_hex);
        end
        fclose(fileID);
        disp('Datos exportados a .txt exitosamente.');
    else
        error('error de cantidad de datos');
    end

catch ME
    disp(['Error: ', ME.message]);
end

clear s;
