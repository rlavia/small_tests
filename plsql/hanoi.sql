
declare
    cantidad_fichas constant pls_integer := 3;
    nivel_de_profundidad constant pls_integer := 7;

    subtype tipo_error is varchar2(100);
    subtype tipo_disco is pls_integer;
    type tipo_pila is VARRAY(10) of tipo_disco;
    type tipo_tablero is VARRAY(3) of tipo_pila;
    type tipo_movimiento is record(origen pls_integer, destino pls_integer);

    resultado tipo_error;
    tablero tipo_tablero;

    procedure inicializar
    is
        movimiento tipo_movimiento;
    begin
        tablero := tipo_tablero(tipo_pila(),tipo_pila(),tipo_pila());
        tablero(1).extend(10);
        tablero(2).extend(10);
        tablero(3).extend(10);
        for i in 1..10 loop
            tablero(1)(i) := 0;
            tablero(2)(i) := 0;
            tablero(3)(i) := 0;
        end loop;
        for i in 1..cantidad_fichas loop
            tablero(1)(i) := cantidad_fichas-i+1;
        end loop;
    end;

    function push_tablero(nro_de_pila in pls_integer, disc in tipo_disco)
    return tipo_error
    is
        i pls_integer;
    begin
        i := 10;
        while tablero(nro_de_pila)(i) = 0
        loop
            i := i - 1;
            exit when i = 0;
        end loop;
        i := i + 1;
        if i &amp;amp;gt; 1 then
            if tablero(nro_de_pila)(i-1) &amp;amp;gt; disc then
                tablero(nro_de_pila)(i) := disc;
            else
                return 'ERROR_INTENTA_COLOCAR_MAYOR_SOBRE_MENOR';
            end if;
        else
            tablero(nro_de_pila)(i) := disc;
        end if;
        return '';
    end;

    function pop_tablero(nro_de_pila in pls_integer, disc out tipo_disco)
    return tipo_error
    is
        i pls_integer;
    begin
        i := 10;
        while tablero(nro_de_pila)(i) = 0
        loop
            i := i - 1;
            exit when i = 0;
        end loop;
        if i &amp;amp;gt; 0 then
            disc := tablero(nro_de_pila)(i);
            tablero(nro_de_pila)(i) := 0;
            return '';
        else
            return 'ERROR_STACK_VACIO';
        end if;
    end;

    function mover_ficha_en_tablero(movimiento in tipo_movimiento)
    return tipo_error
    is
        resultado tipo_error;
        disc tipo_disco;
    begin
        resultado := pop_tablero(movimiento.origen, disc);
        if resultado IS null then
            resultado := push_tablero(movimiento.destino, disc);
            if resultado is null then
                return resultado;
            else
                resultado := push_tablero(movimiento.origen, disc);
                return 'ERROR_NO_SE_PUDO_MOVER_EL_DISCO_DEBIDO_A_UN_ERROR';
            end if;
        else
            null;
        end if;
        return resultado;
    end;

    procedure validar_victoria(path in varchar2)
    is
        valido boolean;
    begin
            valido := true;
            for j in reverse 1..cantidad_fichas loop
                if tablero(2)(j) != cantidad_fichas-j+1 then
                    valido := false;
                end if;
            end loop;
            if valido then
                dbms_output.put_line('=====================================================');
                dbms_output.put_line('=====================================================');
                dbms_output.put_line(path);
                dbms_output.put_line('=====================================================');
                for i in REVERSE 1..10 loop
                    dbms_output.put_line (tablero(1)(i) || '     ' || tablero(2)(i) || '     ' || tablero(3)(i));
                end loop;
                dbms_output.put_line('=====================================================');
            end if;
    end;

    function recorrer_arbol(cant_levels in pls_integer, path in varchar)
    return tipo_error
    is
        movimiento tipo_movimiento;
        movimiento_inverso tipo_movimiento;
    begin
        validar_victoria(path);
        if cant_levels&amp;amp;gt;0 then
            for i in 1..3 loop
                for j in 1..3 loop
                    if i&amp;amp;lt;&amp;amp;gt;j then
                        movimiento.origen := i;
                        movimiento.destino := J;
                        if mover_ficha_en_tablero(movimiento) is null then
                            resultado := recorrer_arbol(cant_levels-1,path || ' (' || movimiento.origen || ',' || movimiento.destino || ') ');
                            movimiento_inverso.origen :=movimiento.destino;
                            movimiento_inverso.destino :=movimiento.origen;
                            if mover_ficha_en_tablero(movimiento_inverso) is not null then
                                DBMS_OUTPUT.put_line('ERROR_CRITICO');
                                return 'ERROR_CRITICO';
                            end if;
                        end if;
                    end if;
                END LOOP;
            END LOOP;
        end if;
        return null;
    end;

begin
  inicializar;
  resultado := recorrer_arbol(nivel_de_profundidad, '');
end;

