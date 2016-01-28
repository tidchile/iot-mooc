require 'test_helper'

class EntitiesControllerTest < ActionController::TestCase
  setup do
    @entity = entities(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:entities)
  end

  test "should create entity" do
    assert_difference('Entity.count') do
      post :create, entity: { name: @entity.name, type: @entity.type }
    end

    assert_response 201
  end

  test "should show entity" do
    get :show, id: @entity
    assert_response :success
  end

  test "should update entity" do
    put :update, id: @entity, entity: { name: @entity.name, type: @entity.type }
    assert_response 204
  end

  test "should destroy entity" do
    assert_difference('Entity.count', -1) do
      delete :destroy, id: @entity
    end

    assert_response 204
  end
end
