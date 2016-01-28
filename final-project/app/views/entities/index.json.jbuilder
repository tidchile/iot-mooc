json.array!(@entities) do |entity|
  json.extract! entity, :id, :name, :type
  json.url entity_url(entity, format: :json)
end
