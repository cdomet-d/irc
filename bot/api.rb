require "oauth2"
require "json"

UID = "u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293"
SECRET = "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"

# Create the client with your credentials
client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")

# Get an access token
token = client.client_credentials.get_token

json_data = JSON.generate(token.token)

File.open("res.json", "w") do |file|
    file.write(json_data)
  end

