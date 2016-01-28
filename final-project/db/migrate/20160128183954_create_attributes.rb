class CreateAttributes < ActiveRecord::Migration
  def change
    create_table :attributes do |t|
      t.references :entity, index: true, foreign_key: true
      t.string :name

      t.timestamps null: false
    end
  end
end
