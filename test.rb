# encoding: utf-8

def test_entropy(file, entropy)
  command = "./etoile -entropy test/#{file}"
  output = `#{command}`
  expected_output = "The entropy is #{entropy} bits.\n"
  if output == expected_output
    print " \e[1;32m✓\e[0m "
  else
    print " \e[31m✗\e[0m "
  end
  puts "#{command} ==> #{expected_output.inspect}"
end

def test_compression
  Dir.glob ("test/*") do |file|
    cmd = "./etoile -zip #{file} |./etoile -unzip /dev/stdin |diff - #{file}"
    if system(cmd)
      print " \e[1;32m✓\e[0m "
    else
      print " \e[31m✗\e[0m "
    end
    puts cmd
  end
end

puts "\e[1mChecking entropy:\e[0m"
test_entropy("random", "7.99")
test_entropy("lorem.txt", "4.13")
puts
puts "\e[1mChecking compression:\e[0m"
test_compression()