class MeasuresController < ApplicationController
  before_action :set_measure, only: [:show, :update, :destroy]
  before_action :set_attribute, only: [:index, :create]

  # GET /measures
  # GET /measures.json
  def index
    period = params[:period]
    if period.present?
      if period == "week"
        @measures = @attribute.measures.where(created_at: Date.today.all_week)
      elsif period == "month"
        @measures = @attribute.measures.where(created_at: Date.today.all_month)
      elsif period == "year"
        @measures = @attribute.measures.where(created_at: Date.today.all_year)
      else
        @measures = @attribute.measures.all
      end
    else
      @measures = @attribute.measures.all
    end

    render json: @measures
  end

  # GET /measures/1
  # GET /measures/1.json
  def show
    render json: @measure
  end

  # POST /measures
  # POST /measures.json
  def create
    @measure = @attribute.measures.new(measure_params)
    if @measure.save
      render json: @measure, status: :created, location: entity_attribute_measure_url(@entity, @attribute, @measure)
    else
      render json: @measure.errors, status: :unprocessable_entity
    end
  end

  # PATCH/PUT /measures/1
  # PATCH/PUT /measures/1.json
  def update
    if @measure.update(measure_params)
      head :no_content
    else
      render json: @measure.errors, status: :unprocessable_entity
    end
  end

  # DELETE /measures/1
  # DELETE /measures/1.json
  def destroy
    @measure.destroy

    head :no_content
  end

  private

  def set_measure
    @measure = Measure.find(params[:id])
  end

  def set_attribute
    @entity = Entity.find_by(name: params[:entity_id])
    @attribute = @entity.entity_attributes.find_by(name: params[:attribute_id])
  end

  def measure_params
    params.require(:measure).permit(:value)
  end
end
