        SqlConnection cn = new SqlConnection();
        SqlCommand cm = new SqlCommand();
        SqlDataReader rs;
        cn.ConnectionString = connectionString;
        cn.Open();
        cm.Connection = cn;
        cm.CommandType = System.Data.CommandType.Text;
        cm.CommandText = &amp;amp;quot;SELECT * FROM tabla WHERE campo = @valor&amp;amp;quot;;
        cm.Parameters.Add(new SqlParameter(&amp;amp;quot;@valor&amp;amp;quot;, valor));
        rs = cm.ExecuteReader(System.Data.CommandBehavior.SingleResult);
        while (rs.Read())
        {
            string s = rs.getString(0);
            Console.WriteLine(s);
        }
        rs.Close();
        cn.Close();
        rs.Dispose();
        cn.Dispose();



