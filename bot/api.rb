require "oauth2"
require "json"

UID = "u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293"
SECRET = ENV["SECRET"]
#TODO: verifier que le SECRET est valide

# Create the client with your credentials
client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")

# Get an access token
token = client.client_credentials.get_token

json_data = JSON.generate(token.token)

File.open("res.json", "w") do |file|
    file.write(json_data)
  end

