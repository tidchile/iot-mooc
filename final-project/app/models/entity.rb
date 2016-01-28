class Entity < ActiveRecord::Base
	has_many :entity_attributes, class_name: "Attribute" 
end
